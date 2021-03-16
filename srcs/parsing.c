/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:56:00 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/16 18:54:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		parsing_hub(char *line, t_lst **cmd_line, char *envp[])
{
	int		i;
	t_lst	*tmp;
	t_cmd	*cmd;

	i = 0;
	tmp = *cmd_line;
	while (line[i])
	{
		cmd = tmp->cmd;
		i = parse_command_line(line, &cmd, i, envp);
		if (i < 0)
			break ;
		if (i < (int)ft_strlen(line))
		{
			printf("Must add second command line\n");
			tmp = add_command_line(tmp);
			tmp = tmp->next;
		}
	}
	return (i);
}

int	parse_command_line(char *line, t_cmd **cmd, int i, char *envp[])
{
	t_cmd	*tmp;
	char	*buffer;

	tmp = cmd[0];
	buffer = ft_calloc(sizeof(char), ft_strlen(line) + 1);
	if (!buffer)
		return (-2);
	while (i >= 0 && line[i])
	{
		if (multiline_character(line, line[i], i))//syntax error
		{
			i = -1;
			break ;
		}
		else if (is_special_character(line[i]) && !in_quotes(line, i))//special carac
		{
			if (line[i] == ';' && i++)
				break ;
			else if (line[i] == ' ')
				i++;
			else if (line[i] == '|')
			{
				if (!add_cmd(&tmp))
				{
					ft_putendl_fd("List memory allocation failed", STDERR);
					break ;
				}
				tmp = tmp->next;
				i++;
			}
			else if (line[i] == '>' || line[i] == '<')
			{
				get_redir_name(line, &i, &buffer, envp);
				if (i != -1)
					tmp->redir_file = copy_buffer_on_array(buffer, tmp->redir_file);
				ft_bzero(buffer, ft_strlen(buffer));
			}
			// = special_action(line, &tmp, i, envp);
		}
		else
		{
			buffer = get_next_token(line, &i, buffer, envp);
			if (!buffer)
				i = -1;
			else
			{
				tmp->token = copy_buffer_on_array(buffer, tmp->token);
				ft_bzero(buffer, ft_strlen(buffer));
			}
		}
			//add buffer to token
	}
	//if (ft_strlen(buffer) == 0 && i != -1)
	//{
	//	printf("BUFFER VIDE\n");
	//	i = -1;
	//}
	//else
	//if (ft_strlen(buffer) != 0)
	//{
	//	tmp->token = copy_buffer_on_array(tmp, buffer, tmp->token);
	//	ft_bzero(buffer, ft_strlen(buffer));
		free(buffer);
	//}
	return (i);;
}

char	*get_next_token(char *line, int *i, char *buffer, char *envp[])
{
	int	j;

	j = ft_strlen(buffer);
	while (line[*i])
	{
		if (!closed_quote(line, *i, line[*i]) && !in_quotes(line, *i))
		{
			print_syntax_error(line[*i]);
			free(buffer);
			return (NULL);
		}
		else if (is_special_character(line[*i]) && !in_quotes(line, *i))
			return (buffer);
		else if (line[*i] == '\\')
			parse_backslash(line, buffer, i, &j);
		else if (line[*i] == '$' && in_quotes(line, *i) != 1)
		{
			parse_dollar(line, i, &buffer, envp);
			j = ft_strlen(buffer);
		}
		else if (line[*i] != '\'' && line[*i] != '\"')
			buffer[j++] = line[*i];
		(*i)++;
	}
	return (buffer);
}
/*ll
int	special_action(char *line, t_cmd **cmd, int i, char *envp[])
{
	char	*buffer;
	if (line[i] == ';' && i++)
		break ;
	else if (line[i] == '|')
	{
		if (!add_cmd(&cmd))
		{
			ft_putendl_fd("List memory allocation failed", STDERR);
			break ;
		}
		cmd = cmd->next;
	}
	else if (line[i] == '>') // to upgrade
		cmd->redir_out = get_redirection(tmp, line, &i, buffer);
	else if (line[i] == '<')
		cmd->redir_in = get_redirection(tmp, line, &i, buffer);
	return (i);
}*/

char	*add_on_buffer(char *buffer, char *to_add, char *line)
{
	int		i;
	char	*join;
	char	*new_buf;

	join = ft_strjoin(buffer, to_add);
	new_buf = ft_calloc(sizeof(char), ft_strlen(line) + ft_strlen(join) + 1);
	i = 0;
	while (new_buf && join && join[i])
	{
		new_buf[i] = join[i];
		i++;
	}
	free(join);
	free(buffer);
	free(to_add);
	return (new_buf);
}

void	parse_dollar(char *line, int *i, char **buffer, char *envp[])
{
	int		j;
	char	*var_name;
	char	*env_value;

	j = 0;
	if (line[*i + 1] == '?')
	{
		(*i)++;
		*buffer = add_on_buffer(*buffer, ft_itoa(exit_value), line);
		return ;
	}
	var_name = ft_calloc(sizeof(char*), ft_strlen(line) + 1);
	if (!var_name)
	{
		*i = -1;
		return ;
	}
	(*i)++;
	while(*i != -1 && line[*i] && is_env_character(line[*i]))
		var_name[j++] = line[(*i)++];
	(*i)--;
	env_value = get_token_value_in_envp(var_name, envp);
	if (!env_value)
	{
		(*buffer)[0] = '$';
		*buffer = add_on_buffer(*buffer, var_name, line);
	}
	else
	{
		*buffer = add_on_buffer(*buffer, env_value, line);
		free(var_name);
	}
}

void	parse_backslash(char *line, char *buffer, int *i, int *j)
{
	if (in_quotes(line, *i) == 0)
		buffer[(*j)++] = line[(*i)++ + 1];
	else if (in_quotes(line, *i) == 1)
		buffer[(*j)++] = line[*i];
	else if (in_quotes(line, *i) == 2)
	{
		if (line[(*i) + 1] && (line[(*i) + 1] == '\\' || line[(*i) + 1] == '$'))
			buffer[(*j)++] = line[(*i)++ + 1];
		else
			buffer[(*j)++] = line[*i];
	}
}

int	is_special_character(char c)
{
	if (c == '|' || c == ' ' || c == '>' || c == '<' || c == ';')
		return (1);
	else
		return (0);
}

int	in_quotes(char *line, int pos)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (line[i] && i <= pos && pos != 0)
	{
		if (line[i] == '\\' && !in_single && !in_double)
			i++;
		else if (line[i] == '\'' && !in_double && i != pos)
			in_single = !in_single;
		else if (line[i] == '\"' && !in_single && i != pos)
			in_double = !in_double;
		i++;
	}
	if (in_single)
		return (1);
	else if (in_double)
		return (2);
	return (0);
}

int	closed_quote(char *line, int pos, char quote_type)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	if (quote_type != '\'' && quote_type != '\"')
		return (1);
	while (line[i])
	{
		if (line[i] == '\\' && !in_quote)
			i++;
		else if (i < pos && line[i] == quote_type)
			in_quote = !in_quote;
		else if (i == pos && in_quote)
			return (1);
		else if (i > pos && line[i] == quote_type)
			return (1);
		i++;
	}
	return (0);
}

char	**copy_buffer_on_array(char *buffer, char **array)
{
	int		i;
	char	**copy_token;

	i = 0;
	//while (head->next != NULL)
	//	head = head->next;
	copy_token = ft_calloc(sizeof(char*), get_length_double_array(array) + 2);
	while (array && array[i])
	{
		//printf("STRDUP: [%s]\n", head->token[i]);
		copy_token[i] = ft_strdup(array[i]);
		i++;
	}
	//printf("BEFORE BUFFER\n");
	//printf("BUFFER: [%s]\n", buffer);
	copy_token[i] = ft_strdup(buffer);
	if (array)
		free_double_array(array);
	return (copy_token);
}

void	print_syntax_error(char c)
{
	ft_putstr_fd(MINISHELL SYNTAX, 2);
	ft_putstr_fd(&c, 2);
	ft_putstr_fd("\n", 2);
}

int	multiline_character(char *line, char c, int i)
{
	int	ret;

	ret = 0;
	//printf("CHARACTER: [%c]\n", c);
	if (c == '\'' || c == '\"')
	{
		if (!closed_quote(line, i, line[i]))
		{
			ret = 1;
			print_syntax_error(c);
		}
	}
	else if(c == '\\' && (i == (int)ft_strlen(line) - 1 || (line[i + 1] && line[i + 1] == ' ')))
	{
		ret = 1;
		print_syntax_error(c);
	}
	else if (c == '|' && i == (int)ft_strlen(line) - 1)
	{
		ret = 1;
		print_syntax_error(c);
	}
	return (ret);
}

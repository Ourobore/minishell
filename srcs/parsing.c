/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:56:00 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/14 20:29:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execution_loop(char *line, char **envp[])
{
	t_cmd	**head;
	int		exit_status;

	exit_status = 0;
	head = malloc(sizeof(*head) * 1);
	head[0] = malloc(sizeof(*head[0]) * 1);
	int i = 0;
	head[0] = allocate_list(head[0]);
	while (head[i])
		i++;
	printf("length: %d\n", i);
	exit_status = parsing_hub(line, &head, *envp);
	i = 0;
	while (head[i])
		i++;
	printf("length 2: %d\n", i);
	//printf("token 0: %s\n", head[0]->token[0]);
	if (exit_status < 0)
		printf("error parsing\n");
	else
	{
		//printf("\n\n");
		//for (int i = 0; head[i] != NULL; i++)
		//{
		//	printf("i: %d\n", i);
		//	for (int j = 0; head[i]->token[j]; j++)
		//	{
		//		printf("j: %d\n", j);
		//		printf("TOKEN: [%s]\n", head[i]->token[j]);
		//	}
		//	printf("\n\n");
		//}
		exit_status = call_builtin_or_pipe(head, line, envp);
	}
	//close redirs
	//add function for full head free
	free_command_list(*head);
	free(head);
	return (exit_status);
}

int		parsing_hub(char *line, t_cmd ***head, char *envp[])
{
	int		i;
	int		j;
	t_cmd	*cmd;

	i = 0;
	j = 0;
	while (line[i])
	{
		printf("LOOP I: %d\tJ: %d\n", i, j);
		cmd = (*head)[j];
		i = parse_command_line(line, &cmd, i, envp);
		if (i < 0)
			break ;
		if (i < (int)ft_strlen(line))
		{
			printf("Must add second command line\n");
			*head = add_command_line(*head);
			j++;
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
			else if (line[i] == '>') // to upgrade
				tmp->redir_out = get_redirection(tmp, line, &i, buffer);
			else if (line[i] == '<')
				tmp->redir_in = get_redirection(tmp, line, &i, buffer);
			// = special_action(line, &tmp, i, envp);
		}
		else
		{
			buffer = get_next_token(line, &i, buffer, envp);
			printf("BUFFER: [%s]\n", buffer);
			tmp->token = copy_buffer_on_array(buffer, tmp->token);
			ft_bzero(buffer, ft_strlen(buffer));
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

	j = 0;
	envp = envp;
	while (line[*i])
	{
		//printf("in\n");
		if (!closed_quote(line, *i, line[*i]))
		{
			ft_putendl_fd("minishell: No multilines", 2);
			return (NULL);
		}
		else if (is_special_character(line[*i]) && !in_quotes(line, *i))
			return (buffer);
		else if (line[*i] == '\\')
			parse_backslash(line, buffer, i, &j);
		//else if (line[*i] == '$' && in_quotes(line, *i) != 1)
		else
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
/*
void	parse_dollar(char *line, int *i, char *buffer, char *envp)
{
	//get_env_variable
	//get_env_value
}
*/
void	parse_backslash(char *line, char *buffer, int *i, int *j)
{
	if (is_in_quotes(line, *i) == 0)
		buffer[(*j)++] = line[(*i)++ + 1];
	else if (is_in_quotes(line, *i) == 1)
		buffer[(*j)++] = line[*i];
	else if (is_in_quotes(line, *i) == 2)
	{
		if (line[(*i) + 1] && (line[(*i) + 1] == '\\' || line[(*i) + 1] == '$'))
			buffer[(*j)++] = line[(*i)++ + 1];
		else
			buffer[(*j)++] = line[*i];
	}
}
t_lst	*add_command_line(t_lst *cmd_line)
{
	t_cmd	*new_cmd;
	t_lst	*new_line;
	t_lst	*tmp;

	new_cmd = ft_calloc(sizeof(*new_cmd), 1);
	new_cmd = allocate_list(new_cmd);
	new_line = ft_calloc(sizeof(*new_line), 1);
	if (!new_cmd || !new_line)
		return (NULL);
	new_line->cmd = new_cmd;
	tmp = cmd_line;
	while (tmp != NULL)
		tmp = tmp->next;
	tmp->next = new_line;
	return (cmd_line);
}
/*
t_cmd	**add_command_line(t_cmd **head)
{
	int		i;
	t_cmd	**new_head;

	i = 0;
	while (head[i] != NULL)
		i++;
	printf("II: %d\n", i);
	new_head = malloc(sizeof(*new_head) * (i + 1));
	i = 0;
	while (head[i] != NULL)
	{
		new_head[i] = head[i];
		i++;
	}
	free(head); // perhaps leaks here
	printf("iii: %d\n", i);
	new_head[i] = malloc(sizeof(*new_head[i]) * 1);
	i = 0;
	while (new_head[i] != NULL)
		i++;
	printf("III: %d\n", i);
	i--;
	new_head[i] = allocate_list(new_head[i]);
	i = 0;
	while (new_head[i] != NULL)
		i++;
	printf("IIII: %d\n", i);
	return (new_head);	
}
*/
t_cmd	*copy_command_line(t_cmd **head, t_cmd **new_head, int i)
{
	new_head[i]->token = head[i]->token;
	new_head[i]->file_in = head[i]->file_in;
	new_head[i]->file_out = head[i]->file_out;
	new_head[i]->redir_in = head[i]->redir_in;
	new_head[i]->redir_out = head[i]->redir_out;
	new_head[i]->ret = head[i]->ret;
	new_head[i]->next = head[i]->next;
	return (new_head[i]);
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
		else if (line[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (line[i] == '\"' && !in_single)
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

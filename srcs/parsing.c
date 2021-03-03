/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:56:00 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/02 21:39:32 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_line(char *line, t_cmd **head, int i, char *envp[])
{
	int		j;
	char	*buffer;
	int		exit_status;
	t_cmd	*tmp;

	j = 0;
	exit_status = 0;
	tmp = *head;
	buffer = ft_calloc(sizeof(char), ft_strlen(line) + 1);
	//printf("LINE LENGTH: [%ld]\n", ft_strlen(line));
	while (line[i] && i < (int)ft_strlen(line) && exit_status != -1 && exit_status != 255)
	{
		//printf("VERIF LINE[I]: [%c]\n", line[i]);
		//printf("VERIF BUFFER [%d]: [%s]\n", i, buffer);
		if (multiline_character(line, line[i], i) == -1)
		{
			printf("In Multiline\n");
			i = -1;
			break ;
		}
		else if (is_special_character(line[i]) && !is_in_quotes(line, i))
		{
			add_to_token(&tmp, &buffer);
			free(buffer);
			buffer = ft_calloc(sizeof(char), ft_strlen(line) + 1);
			j = 0;
			if (line[i] == ';' && i++)
				break ;
			else if (line[i] == '|')
			{
				if (!add_cmd(&tmp))
				{
					ft_putendl_fd("List memory allocation failed", STDERR);
					break ;
				}
				tmp = tmp->next;
			}
			else if (line[i] == '>') // to upgrade
				tmp->redir_out = get_redirection(tmp, line, &i, buffer);
			else if (line[i] == '<')
				tmp->redir_in = get_redirection(tmp, line, &i, buffer);
		}
		else if (line[i] == '\\' && line[i + 1])
		{
			if (is_in_quotes(line, i) == 0)
				buffer[j++] = line[i++ + 1];
			else if (is_in_quotes(line, i) == 1)
				buffer[j++] = line[i];
			else if (is_in_quotes(line, i) == 2)
			{
				if (line[i + 1] && (line[i + 1] == '\\' || line[i + 1] == '$'))
					buffer[j++] = line[i++ + 1];
				else
					buffer[j++] = line[i];
			}
		}
		else if (line[i] == '$' && is_in_quotes(line, i) != 1)
		{
			char	*env_var;
			char	*tmp_buffer;
			env_var = get_env_variable(line, &i, envp);
			printf("BUFFER BEFORE: [%s]\n", buffer);
			printf("ENV VAR BEFORE: [%s]\n", env_var);
			tmp_buffer = ft_strdup(buffer);
			free(buffer);
			buffer = ft_calloc(sizeof(char), ft_strlen(line) + ft_strlen(env_var) + 1);
			if (!buffer)
				return(-1); // to adjust
			int	y = 0;
			j = 0;
			while (tmp_buffer[y])
				buffer[j++] = tmp_buffer[y++];
			y = 0;
			while(env_var[y])
				buffer[j++] = env_var[y++]; 
			//buffer = ft_strjoin(tmp_buffer, env_var);
			//j = ft_strlen(buffer);
			free(tmp_buffer);
			free(env_var);
		}
		
		else if (line[i] && (is_in_quotes(line, i) || (line[i] != '\'' && line[i] != '\"')))
			buffer[j++] = line[i];
		//else if (line[i] != '\'' && line[i] != '\"')
		//	buffer[j++] = line[i];
		i++;
	}
	//if ()
	//if (ft_strlen(tmp->token[0]) == 0)
	//	ft_putendl_fd("Syntax error near '|'", 2);
		//free everything
	//printf("VERIF OUT LINE[I]: [%c]\n", line[i]);
	//printf("VERIF OUT BUFFER [%d]: [%s]\n", i, buffer);
	if (i == -1)
		return (-1);
	add_to_token(&tmp, &buffer); //add free buffer to add_to_token
	for(int g = 0; g < (int)get_length_double_array(tmp->token); g++)
		printf("TOKEN: [%s]\n", tmp->token[g]);
	//exit_status = call_builtin_or_pipe(head, buffer, envp);
	free(buffer);
	//printf("LENGTH [%ld]\t I [%d]\n", ft_strlen(line), i);
	return (i);
}

int	multiline_character(char *line, char c, int i)
{
	int	ret;

	ret = 0;
	printf("CHARACTER: [%c]\n", c);
	if (c == '\'' || c == '\"')
	{
		if (!verify_quote(line, c, i))
		{
			ret = -1;
			print_syntax_error(c);
		}
	}
	else if(c == '\\' && (i == (int)ft_strlen(line) - 1 || (line[i + 1] && line[i + 1] == ' ')))
	{
		ret = -1;
		print_syntax_error(c);
	}
	else if (c == '|' && i == (int)ft_strlen(line) - 1)
	{
		ret = -1;
		print_syntax_error(c);
	}
	return (ret);
}

void	print_syntax_error(char c)
{
	ft_putstr_fd(MINISHELL SYNTAX, 2);
	ft_putstr_fd(&c, 2);
	ft_putstr_fd("\n", 2);
}

void add_to_token(t_cmd **tmp, char **buffer)
{
	if (ft_strlen(*buffer) != 0)
	{
		(*tmp)->token = copy_buffer_on_token(*tmp, *buffer);
		ft_bzero(*buffer, ft_strlen(*buffer));
	}
}

char	**copy_buffer_on_token(t_cmd *head, char *buffer)
{
	int		i;
	char	**copy_token;

	i = 0;
	while (head->next != NULL)
		head = head->next;
	copy_token = ft_calloc(sizeof(char*), get_length_double_array(head->token) + 2);
	while (head->token && (head->token)[i])
	{
		//printf("STRDUP: [%s]\n", head->token[i]);
		copy_token[i] = ft_strdup((head->token)[i]);
		i++;
	}
	//printf("BEFORE BUFFER\n");
	//printf("BUFFER: [%s]\n", buffer);
	copy_token[i] = ft_strdup(buffer);
	if (head->token)
		free_double_array((head->token));
	return (copy_token);
}

int	is_special_character(char c)
{
	if (c == ';' || c == '|' || c == ' ' || c == '>' || c == '<')
		return (1);
	else
		return (0);
}

int	is_in_quotes(char *line, int pos)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (line[i])
	{
		if (i == pos && (i != 0 && line[i - 1] != '\\') && ((line[i] == '\'' && in_single) || (line[i] == '\"' && in_double)))
			return (0);
		if (i < pos)
		{
			if (line[i] == '\'' && (i != 0 && line[i - 1] != '\\'))
				in_single = !in_single;
			else if (line[i] == '\"' && (i != 0 && line[i - 1] != '\\'))
				in_double = !in_double;
		}
		if (i > pos)
		{
			if (line[i] == '\'' && (i != 0 && line[i - 1] != '\\') && in_single)
				return (1);
			else if (line[i] == '\"' && (i != 0 && line[i - 1] != '\\') && in_double)
				return (2);
		}
		i++;
	}
	return (0);
}

int	verify_quote(char *line, char c, int pos)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (line[i] && i < pos)
	{
		if (line[i] == '\'' && is_in_quotes(line, i) != 1 && (i > 0 && line[i - 1] != '\\'))
		if (i == pos && c == '\'' && in_single)
			return (1);
		else if (i == pos && c == '\"' && in_double)
			return (1);
		if (line[i] == '\'' && !in_double && !is_in_quotes(line, i) && (i != 0 && line[i - 1] != '\\'))
			return (1);
		else if (line[i] == '\"' && !in_single && !is_in_quotes(line, i) && (i != 0 && line[i - 1] != '\\'))
			return (1);
		i++;
	}
	if ((c == '\'' && in_single) || (c == '\"' && in_double))
		return (1);
	else
		return (0);
}

/*
	i = 0;
	in_single = 0;
	in_double = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double)
			in_single = !in_single;
		if (line[i] == '\"' && !in_single)
			in_double = !in_double;
		i++;
	}
	if (in_single || in_double)
		return (1);
	else
		return (0);
		
}*/

//verif redirections

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:56:00 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/20 08:44:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing_hub(char *line, char *envp[], int mode)
{
	int		i;
	//t_cmd	*cmd;

	i = 0;
	envp = envp;
	while (line[i])
	{
		add_cmd(&(g_shell.cmd));
		i = parse_command_line(g_shell.line, &(g_shell.cmd), i, g_shell.envp_copy);
		if (mode == 1)
			call_builtin_or_pipe(g_shell.cmd, &(g_shell.envp_copy));
		free_command_list(g_shell.cmd);
		g_shell.cmd = NULL;
		if (i < 0)
			break ;
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
		if (is_special_character(line[i]) && !in_quotes(line, i))
		{
			if (line[i] == '>' || line[i] == '<')
				parse_redirection(line, &tmp, &i, envp);
			else if (special_action(line, &tmp, &i) != 1)
				break ;
		}
		else
		{
			buffer = get_next_token(&i, buffer, envp, 1);
			if (i >= 0)
				tmp->token = copy_buffer_on_array(&buffer, tmp->token);
		}
	}
	free(buffer);
	return (i);
}

char	*get_next_token(int *i, char *buffer, char *envp[], int mode)
{
	int		j;
	char	*line;

	j = ft_strlen(buffer);
	line = g_shell.line;
	while (*i >= 0 && line[*i])
	{
		if (multiline_character(line, line[*i], i, mode))
			break ;
		if (is_special_character(line[*i]) && !in_quotes(line, *i))
			return (buffer);
		else if (line[*i] == '\\')
			parse_backslash(line, buffer, i, &j);
		else if (line[*i] == '$' && in_quotes(line, *i) != 1)
		{
			parse_dollar(line, i, &buffer, envp);
			j = ft_strlen(buffer);
		}
		else if ((line[*i] == '\'' || line[*i] == '\"') && in_quotes(line, *i))
			buffer[j++] = line[*i];
		else if (line[*i] != '\'' && line[*i] != '\"')
			buffer[j++] = line[*i];
		(*i)++;
	}
	return (buffer);
}

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

char	**copy_buffer_on_array(char **buffer, char **array)
{
	int		i;
	char	**copy_token;

	i = 0;
	copy_token = ft_calloc(sizeof(char *), get_length_double_array(array) + 2);
	while (array && array[i])
	{
		copy_token[i] = ft_strdup(array[i]);
		i++;
	}
	copy_token[i] = ft_strdup(*buffer);
	if (array)
		free_double_array(array);
	ft_bzero(*buffer, ft_strlen(*buffer));
	return (copy_token);
}

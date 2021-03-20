/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 10:24:39 by user42            #+#    #+#             */
/*   Updated: 2021/03/20 08:12:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	special_action(char *line, t_cmd **cmd, int *i)
{
	printf("in special action\n");
	if (line[*i] == ';')
	{
		if (get_length_double_array((*cmd)->token) == 0)
		{
			print_syntax_error(line[*i]);
			*i = -1;
			return (-1);
		}
		(*i)++;
		return (2);
	}
	else if (line[*i] == ' ')
		(*i)++;
	else if (line[*i] == '|' && !multiline_character(line, line[*i], i, 1))
	{
		if (!add_cmd(cmd))
		{
			ft_putendl_fd("List memory allocation failed", STDERR);
			*i = -2;
			return (-2);
		}
		*cmd = (*cmd)->next;
		(*i)++;
	}
	return (1);
}

void	parse_redirection(char *line, t_cmd **cmd, int *i, char *envp[])
{
	char	*buffer;

	buffer = ft_calloc(sizeof(char *), ft_strlen(line) + 1);
	if (!buffer)
	{
		*i = -2;
		return ;
	}
	get_redir_name(line, i, &buffer, envp);
	if (*i != -1)
		(*cmd)->redir_file = copy_buffer_on_array(&buffer, (*cmd)->redir_file);
	free(buffer);
}

void	parse_dollar(char *line, int *i, char **buffer, char *envp[])
{
	int		j;
	char	*var_name;
	char	*value;

	if (line[*i + 1] == '?')
	{
		(*i)++;
		*buffer = add_on_buffer(*buffer, ft_itoa(g_shell.exit_value), line);
		return ;
	}
	var_name = ft_calloc(sizeof(char *), ft_strlen(line) + 1);
	if (!var_name)
	{
		*i = -2;
		return ;
	}
	(*i)++;
	j = 0;
	while(*i != -1 && line[*i] && is_env_character(line[*i]))
		var_name[j++] = line[(*i)++];
	(*i)--;
	value = get_token_value_in_envp(var_name, envp);
	store_dollar(line, buffer, var_name, value);
}

void	store_dollar(char *line, char **buffer, char *var_name, char *value)
{
	if (!value)
	{
		(*buffer)[0] = '\0';
		free(var_name);
		*buffer = add_on_buffer(*buffer, NULL, line);
	}
	else
	{
		free(var_name);
		*buffer = add_on_buffer(*buffer, value, line);
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

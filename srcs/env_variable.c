/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:44:18 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/20 11:32:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_env_variable(char *token, char *envp[])
{
	int	is_in_envp;

	is_in_envp = search_token_in_envp(token, envp);
	if (is_in_envp == -1)
		return (0);
	else
		return (is_in_envp);
}

int		is_env_character(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (\
c >= '0' && c <= '9') || c == '_' || c == '=')
		return (1);
	else
		return (0);
}

int		valid_token(char *token)
{
	int	i;

	i = 0;
	while (token[i] && token[i] != '=')
	{
		if (!is_env_character(token[i]))
			return (0);
		i++;
	}
	return (1);
}

void	get_redir_name(char *line, int *i, char **buffer, char *envp[])
{
	int	redir_type;

	redir_type = get_redir_type(line, i, buffer);
	(*i)++;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	*buffer = get_next_token(i, *buffer, envp, 0);
	if (((redir_type == 1 || redir_type == 2) && ft_strlen(*buffer) == 2) || (\
		redir_type == 3 && ft_strlen(*buffer) == 3))
	{
		if (redir_type == 1)
			print_syntax_error('<');
		else
			print_syntax_error('>');
		*i = -1;
	}
}

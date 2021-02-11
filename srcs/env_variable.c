/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:44:18 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/11 16:21:34 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*inversion_variable_value(char *token, char *envp[])
{
	char	*value;

	value = NULL;
	value = get_token_value_in_envp(token, envp);
	if (!value)
	{
		free(token);
		token = value;
	}
	return (token);
}

int	is_env_variable(char *token, char *envp[])
{
	int	is_in_envp;

	is_in_envp = search_token_in_envp(token, envp);
	if (is_in_envp == -1)
		return (0);
	else
		return (1);
}

char	**env_variable_expansion(char **command_line, char *envp[])
{
	int		i;
	char	*expansion;

	i = 0;
	while (command_line[i])
	{
		if (command_line[i][0] == '$' && \
is_env_variable(&(command_line[i][1]), envp))
		{
			expansion = get_token_value_in_envp(&(command_line[i][1]), envp);
			free(command_line[i]);
			command_line[i] = expansion;
		}
		i++;
	}
	return (command_line);
}

int	detect_dollar_sign(char **token)
{
	int	i;
	int	j;

	i = 0;
	while (token[i])
	{
		j = 0;
		while (token[i][j])
		{
			if (token[i][j] == '$' && token[i][j + 1] && token[i][j + 1] != '?')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

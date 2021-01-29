/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:23:56 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/29 18:39:01 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_unset(char **token, char **envp[])
{
	int	i;
	int	token_index;
	int	exit_status;

	i = 1;
	while (token[i])
	{
		token_index = search_token_in_envp(token[i], *envp);
		if (token_index != -1)
			exit_status = remove_token_in_envp(token_index, envp);
		i++;
	}
	return (exit_status);
}

int	characters_before_equal(char *token)
{
	int	i;

	i = 0;
	while (token[i] && token[i] != '=')
		i++;
	return (i);
}

int	search_token_in_envp(char *token, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(token, envp[i], characters_before_equal(token)) == 0 && (\
envp[i][characters_before_equal(token)] == '=' || \
envp[i][characters_before_equal(token)] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int	remove_token_in_envp(int token_index, char **envp[])
{
	int		i;
	int		j;
	int		exit_status;
	char	**new_envp;

	exit_status = 1;
	new_envp = NULL;
	new_envp = ft_calloc(sizeof(char*), get_length_double_array(*envp));
	if (!new_envp)
		return (exit_status);
	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		if (i != token_index)
			new_envp[j++] = ft_strdup((*envp)[i++]);
		else
		{
			exit_status = 0;
			i++;
		}
	}
	//free_double_array(envp);
	*envp = new_envp;
	return (exit_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 09:23:56 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/09 14:26:26 by lchapren         ###   ########.fr       */
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
	(void)exit_status;
	return (0);
}

int	characters_before_equal(char *token)
{
	int	i;

	i = 0;
	while (token[i] && token[i] != '=')
		i++;
	return (i);
}

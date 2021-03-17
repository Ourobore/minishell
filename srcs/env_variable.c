/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:44:18 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/17 14:31:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_env_variable(char *token, char *envp[])
{
	int	is_in_envp;

	is_in_envp = search_token_in_envp(token, envp);
	if (is_in_envp == -1)
		return (0);
	else
		return (is_in_envp);
}

int	is_env_character(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (\
c >= '0' && c <= '9') || c == '_')
		return (1);
	else
		return (0);
}

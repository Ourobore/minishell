/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 08:56:51 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/28 14:44:56 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Without arguments and option, env does not sort alphabetically his variables
*/

int	builtin_env(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (1);
}

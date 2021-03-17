/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 08:56:51 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/17 18:24:02 by user42           ###   ########.fr       */
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
		ft_putendl_fd(envp[i], 1);
		i++;
	}
	return (0);
}

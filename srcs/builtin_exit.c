/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:49:32 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/19 19:03:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_exit(char **command)
{
	int	length;
	int	exit_status;

	ft_putendl_fd("exit", 1);
	length = get_length_double_array(command);
	if (length > 2)
	{
		ft_putendl_fd(MINISHELL "exit: too many arguments", 2);
		return (1);
	}
	else
	{
		if (length == 1)
			exit_status = g_shell.exit_value;
		else
			exit_status = ft_atoi(command[1]);
		free_shell_data(1);
		exit(exit_status);
	}
	return (0);
}

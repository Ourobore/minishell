/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:49:32 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/18 15:25:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_exit(char **command, t_lst *cmd_line)
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
			exit_status = g_cmd_line->exit_value;
		else
			exit_status = ft_atoi(command[1]);
		free_command_line(cmd_line, 2);
		//free_double_array(envp);
		exit(exit_status);
	}
	return (0);
}

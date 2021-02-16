/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:49:32 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/12 15:22:03 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_exit(char *line)
{
	if (ft_strcmp(line, "exit") == 0)
	{
		//printf("in exit\n");
		return (-1);
	}
	else
		return (1);
}

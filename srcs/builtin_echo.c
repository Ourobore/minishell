/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:18:29 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/14 19:01:02 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_echo(char **token)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (ft_strcmp(token[1], "-n") == 0)
	{
		i = 2;
		newline = 0;
	}
	while (token[i])
	{
		ft_putstr_fd(token[i], 1);
		if (token[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (1);
}

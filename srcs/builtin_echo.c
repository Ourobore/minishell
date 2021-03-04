/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:18:29 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/04 13:25:01 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_echo(char **token)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (get_length_double_array(token) > 1 && ft_strcmp(token[1], "-n") == 0)
	{
		i = 2;
		new_line = 0;
	}
	while (token[i])
	{
		ft_putstr_fd(token[i], STDOUT);
		if (token[i + 1])
			ft_putchar_fd(' ', STDOUT);
		i++;
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT);
	return (0);
}

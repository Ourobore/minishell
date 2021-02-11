/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:53:52 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/07 10:57:45 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	prompt_line(char **line)
{
	ft_putstr_fd("lchapren@minishell $ ", 1);
	get_next_line(0, line);
	//if else to check if entry is NULL?
	//if (ft_strcmp(*line, "exit") == 0)
	//	return (0);
	//else
	return (1);
}

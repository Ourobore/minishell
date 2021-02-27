/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:53:52 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/23 20:40:07 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prompt_line(void)
{
	char	*line;

	ft_putstr_fd("lchapren@minishell $ ", 1);
	if (get_next_line(0, &line) == -1)
		return (NULL);
	//if else to check if entry is NULL?
	//if (ft_strcmp(*line, "exit") == 0)
	//	return (0);
	//else
	return (line);
}

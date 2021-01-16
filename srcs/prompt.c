/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:53:52 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/16 09:08:24 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	prompt_line(char **line)
{
	ft_putstr_fd("minishell@ayuroyet-lchapren $ ", 1);
	get_next_line(0, line);
	if (ft_strcmp(*line, "exit") == 0)
		return (0);
	else
		return (1);
}

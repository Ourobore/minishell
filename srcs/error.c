/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 14:28:04 by user42            #+#    #+#             */
/*   Updated: 2021/03/17 18:47:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_syntax_error(char c)
{
	ft_putstr_fd(MINISHELL SYNTAX, 2);
	ft_putstr_fd(&c, 2);
	ft_putstr_fd("\n", 2);
}

void	print_not_valid_idendifier(char *token)
{
	ft_putstr_fd(MINISHELL"export: ", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd(": not a valid identifier", 2);
}
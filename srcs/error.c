/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 14:28:04 by user42            #+#    #+#             */
/*   Updated: 2021/03/20 11:36:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_syntax_error(char c)
{
	ft_putstr_fd(MINISHELL, 2);
	ft_putstr_fd(SYNTAX, 2);
	write(2, &c, 1);
	ft_putstr_fd("\n", 2);
}

void	print_not_valid_idendifier(char *token)
{
	ft_putstr_fd(MINISHELL"export: ", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd(": not a valid identifier", 2);
}

void	error_malloc(void)
{
	ft_putendl_fd("Malloc allocation error. Exit", 2);
	free_shell_data(2);
	exit(1);
}

int		pipe_handling(char *line, t_cmd **cmd, int *i)
{
	if (!get_length_double_array((*cmd)->token) && \
		!get_length_double_array((*cmd)->redir_file))
	{
		print_syntax_error(line[*i]);
		*i = -1;
		return (-1);
	}
	else if (!add_cmd(cmd))
	{
		ft_putendl_fd("List memory allocation failed", STDERR);
		*i = -2;
		return (-2);
	}
	return (0);
}

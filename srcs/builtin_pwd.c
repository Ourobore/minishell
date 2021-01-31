/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:14:07 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/29 22:03:33 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = get_pwd();
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
	return (0);
}

char	*get_pwd(void)
{
	char	*pwd;
	size_t	buf_size;

	pwd = NULL;
	buf_size = 1;
	pwd = getcwd(pwd, buf_size);
	while (errno == ERANGE)
	{
		errno = 0;
		buf_size++;
		pwd = getcwd(pwd, buf_size);
	}
	return (pwd);
}

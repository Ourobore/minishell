/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:23:28 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/01 10:30:47 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	directory_exists(char *dir_path)
{
	int		exit_status;
	char	*pwd;

	pwd = get_pwd();
	if (chdir(dir_path) == -1)
		exit_status = 0;
	else
	{
		chdir(pwd);
		exit_status = 1;
	}
	free(pwd);
	return (exit_status);
}
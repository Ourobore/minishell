/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:23:28 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/13 16:11:03 by lchapren         ###   ########.fr       */
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

int	is_absolute_or_relative_path(char *path)
{
	if (ft_strncmp(path, "/", 1) == 0)
		return (1);
	if (ft_strncmp(path, "./", 2) == 0 || (ft_strncmp(path, "../", 3) == 0))
		return (2);
	return (0);
}

char	**get_env_path(char *envp[])
{
	char	*path_value;
	char	**path;

	path_value = NULL;
	path_value = get_token_value_in_envp("PATH", envp);
	if (!path_value)
		return (NULL);
	path = ft_split(path_value, ':');
	free(path_value);
	if (!path)
		return (NULL);
	return (path);
}

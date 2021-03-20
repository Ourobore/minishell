/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:23:28 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/20 10:47:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		directory_exists(char *dir_path)
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

int		is_absolute_or_relative_path(char *path)
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

void	open_close_pipes(int *pipefd, int nb_pipes, int mode)
{
	int	i;

	i = 0;
	if (mode == 1)
	{
		while (i < nb_pipes)
		{
			pipe(pipefd + 2 * i);
			i++;
		}
	}
	if (mode == 2)
	{
		while (i < nb_pipes * 2)
		{
			close(pipefd[i]);
			i++;
		}
		free(pipefd);
	}
}

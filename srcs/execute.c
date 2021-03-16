/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 08:27:18 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/16 18:48:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_command(char **command, char *envp[])
{
	char	**path;
	char	*exec_path;

	if (is_absolute_or_relative_path(command[0]))
	{
		if (execve(command[0], command, envp) == -1)
			ft_putendl_fd(strerror(errno), STDERR);
	}
	else
	{
		path = get_env_path(envp);
		exec_path = search_executable_in_path(command[0], path);
		free_double_array(path);
		if (exec_path)
			if (execve(exec_path, command, envp) == -1)
				ft_putendl_fd(strerror(errno), STDERR);
		free(exec_path);
	}
	return (1);
}

char	*search_executable_in_path(char *executable, char **path)
{
	int		i;
	char	*exec_path;

	i = 0;
	while (path[i])
	{
		if (directory_exists(path[i]))
		{
			exec_path = search_executable_in_dir(executable, path[i]);
			if (exec_path)
				return (exec_path);
		}
		i++;
	}
	return (NULL);
}

char	*search_executable_in_dir(char *executable, char *path)
{
	DIR				*dir;
	struct dirent	*entity;
	char			*exec_path;

	dir = opendir(path);
	entity = readdir(dir);
	while (entity)
	{
		if (ft_strcmp(entity->d_name, executable) == 0)
		{
			exec_path = is_an_executable(path, entity->d_name);
			if (exec_path)
			{
				closedir(dir);
				return (exec_path);
			}
		}
		entity = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

char	*is_an_executable(char *file_path, char *file_name)
{
	int				exit_status;
	char			*path;
	char			*executable;
	struct stat		buf;

	path = ft_strjoin(file_path, "/");
	executable = ft_strjoin(path, file_name);
	exit_status = stat(executable, &buf);
	free(path);
	if (exit_status == -1)
		return (NULL);
	if (S_ISDIR(buf.st_mode))
		return (NULL);
	if ((buf.st_mode & S_IXOTH) != S_IXOTH && (\
buf.st_mode & S_IXGRP) != S_IXGRP && (\
buf.st_mode & S_IXUSR) != S_IXUSR)
		return (NULL);
	return (executable);
}

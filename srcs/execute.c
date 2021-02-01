/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 08:27:18 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/01 10:38:51 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_command(char **command, char *envp[])
{
	char	**path;
	char	*exec_path;

	if (is_absolute_or_relative_path(command[0]))
		execute_path(command[0], command, envp);
	else
	{
		path = get_env_path(envp);
		exec_path = search_executable_in_path(command[0], path);
		if (exec_path)
			execute_path(exec_path, command, envp);
		free(exec_path);
		free_double_array(path);
	}
	return (1);
}

int		execute_path(char *exec_path, char **command, char *envp[])
{
	int	child_pid;
	int	status;

	child_pid = fork();
	if (child_pid == 0)
		execve(exec_path, command, envp);
	else
		wait(&status);
	return (1);
}

char	*search_executable_in_path(char *executable, char **path)
{
	int				i;
	DIR				*dir;
	struct dirent	*entity;
	char			*exec_path;

	i = 0;
	while (path[i])
	{
		if (directory_exists(path[i]))
		{
			dir = opendir(path[i]);
			entity = readdir(dir);
			while(entity)
			{
				if (ft_strcmp(entity->d_name, executable) == 0)
				{
					exec_path = is_an_executable(path[i], entity->d_name);
					if (exec_path)
						return (exec_path);
				}
				entity = readdir(dir);
			}
			closedir(dir);
		}
		i++;
	}
	return (NULL);
}

char	*is_an_executable(char *file_path, char *file_name)
{
	int				exit_status;
	char			*path;
	char			*executable;
	struct	stat	buf;

	path = ft_strjoin(file_path, "/");
	executable = ft_strjoin(path, file_name);
	exit_status = stat(executable, &buf);
	free(path);
	if (exit_status == -1)
		return (NULL);
	if (S_ISDIR(buf.st_mode))
		return (NULL);
	if ((buf.st_mode & S_IXOTH) != S_IXOTH && \
(buf.st_mode & S_IXGRP) != S_IXGRP && \
(buf.st_mode & S_IXUSR) != S_IXUSR)
		return (NULL);
	return (executable);
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

char	*inversion_variable_value(char *token, char *envp[])
{
	char	*value;

	value = NULL;
	value = get_token_value_in_envp(token, envp);
	if (!value)
	{
		free(token);
		token = value;
	}
	return (token);
}

int	is_env_variable(char *token, char *envp[])
{
	int	is_in_envp;

	is_in_envp = search_token_in_envp(token, envp);
	if (is_in_envp == -1)
		return (0);
	else
		return (1);
}

int	detect_dollar_sign(char **token)
{
	int	i;
	int	j;

	i = 0;
	while (token[i])
	{
		j = 0;
		while (token[i][j])
		{
			if (token[i][j] == '$' && token[i][j + 1] && token[i][j + 1] != '?')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

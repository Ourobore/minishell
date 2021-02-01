/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:47:55 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/01 09:50:03 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char *envp[])
{
	int		prompt_loop;
	char	*line;
	char	**envp_copy;
	
	argc = argc;
	argv = argv;
	prompt_loop = 1;
	envp_copy = copy_envp(envp);
/*
	DIR	*dir;
	struct dirent *entity;
	//dir = NULL;
	dir = opendir(".");
	entity = readdir(dir);
	int ret;
	struct stat buf;
	while (entity)
	{
		ret = stat(entity->d_name, &buf);
		ret++;
		printf("%s [%u] {%u} (%d) |%d|\n", entity->d_name, entity->d_type, entity->d_reclen, buf.st_mode, buf.st_mode & S_IXGRP);
		entity = readdir(dir);
	}
	closedir(dir);*/
	if (!envp_copy)
		return (1) ;
	while (prompt_loop > 0)
	{
		prompt_line(&line);
		prompt_loop = builtin_exit(line);
		tokenization(line, &envp_copy);
		free(line);
	}
	free_double_array(envp_copy);
	//Free function
	return (0);
}

char **copy_envp(char *envp[])
{
	int		i;
	int		length;
	char	**copy;

	length = get_length_double_array(envp);
	copy = NULL;
	copy = ft_calloc(sizeof(char*), length + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	return (copy);
}

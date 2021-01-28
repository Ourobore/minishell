/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:46:39 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/17 08:49:03 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(char *path)
{
	int		i;
	int		ret;
	char	**token;

	i = 0;
	ret = 0;
	if (path[0] == '/')
		chdir("/");
	token = ft_split(path, '/');
	while (token[i] && ret == 0)
	{
		//printf("%d: %s\n", i, token[i]);
		if (is_directory(token[i]))
			chdir(token[i]);
		else
			ret = -1;
		
		i++;
	}
	free_double_array(token);
	//pwd = builtin_pwd(); 
	return (ret);
}

int	is_directory(char *token)
{
	int				is_dir;
	DIR				*dir;
	struct dirent*	entity;

	is_dir = 0;
	dir = NULL;
	dir = opendir(".");
	entity = readdir(dir);
	while (entity)
	{
		//printf("TYPE: %u | NAME: %s\n", entity->d_type, entity->d_name);
		if (entity->d_type == DT_DIR && ft_strcmp(entity->d_name, token) == 0)
			is_dir = 1;
		entity = readdir(dir);
	}
	//printf("IS_DIR: %d\n", is_dir);
	closedir(dir);
	return (is_dir);
}
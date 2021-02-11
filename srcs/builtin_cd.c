/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:46:39 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/09 14:17:15 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(char **token, char **envp[])
{
	int		ret;
	char	*oldpwd;
	char	*home_path;

	ret = 0;
	oldpwd = get_pwd();
	ret = verify_cd_args(token, *envp);
	if (ret == 1)
	{
		home_path = get_token_value_in_envp("HOME", *envp);
		chdir(home_path);
		free(home_path);
	}
	if (ret == 0)
		chdir(token[1]);
	update_pwd_envp(oldpwd, envp);
	//free_double_array(token);
	return (0);
}

int	verify_cd_args(char **token, char *envp[])
{
	int		exit_status;
	int		nb_args;

	nb_args = nb_cd_args(token);
	if (nb_args == 0)
	{
		if (search_token_in_envp("HOME", envp) == -1)
		{
			ft_putendl_fd("bash: cd: HOME not set", STDERR);
			return (-1);
		}
		return (1);
	}
	else if (nb_args > 1)
	{
		ft_putendl_fd("bash: cd: too many arguments", STDERR);
		return (2);
	}
	else
	{
		exit_status = directory_exists(token[1]);
		if (exit_status == -1)
		{
			ft_putendl_fd(strerror(errno), STDERR);
			return (-2);
		}
		return (0);
	}
}

void	update_pwd_envp(char *oldpwd, char **envp[])
{
	char	*pwd;
	char	*join_pwd;
	char	*join_oldpwd;

	pwd = get_pwd();
	join_pwd = ft_strjoin("PWD=", pwd);
	join_oldpwd = ft_strjoin("OLDPWD=", oldpwd);
	modify_token_in_envp(join_pwd, search_token_in_envp("PWD", *envp), envp);
	modify_token_in_envp(join_oldpwd, search_token_in_envp("OLDPWD", *envp), envp);
	free(pwd);
	free(oldpwd);
	free(join_pwd);
	free(join_oldpwd);
}

int	nb_cd_args(char **token)
{
	int i;

	i = 1;
	while (token[i])
		i++;
	return (i - 1);
}

/*
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
*/
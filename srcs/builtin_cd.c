/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 17:46:39 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/17 19:31:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(char **token, char **envp[])
{
	int		ret;
	int		exit_status;
	char	*oldpwd;

	exit_status = 0;
	ret = verify_cd_args(token, *envp);
	if (ret != 0 && ret != 1)
		return (exit_status);
	oldpwd = get_pwd();
	exit_status = change_directory(token, *envp, ret);
	update_pwd_envp(oldpwd, envp);
	return (exit_status);
}

int	change_directory(char **token, char *envp[], int ret)
{
	char	*home_path;

	if (ret == 1)
	{
		home_path = get_token_value_in_envp("HOME", envp);
		chdir(home_path);
		free(home_path);
	}
	if (ret == 0)
	{
		if (chdir(token[1]) == -1)
		{
			ft_putstr_fd(MINISHELL"cd: ", 2);
			ft_putendl_fd(strerror(errno), 2);
			return (1);
		}
	}
	return (0);
}

int	verify_cd_args(char **token, char *envp[])
{
	if (nb_cd_args(token) == 0)
	{
		if (search_token_in_envp("HOME", envp) == -1)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR);
			return (-1);
		}
		return (1);
	}
	else if (nb_cd_args(token) > 1)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR);
		return (2);
	}
	else
	{
		if (directory_exists(token[1]) == -1)
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
	modify_token_in_envp(join_oldpwd, \
search_token_in_envp("OLDPWD", *envp), envp);
	free(pwd);
	free(oldpwd);
	free(join_pwd);
	free(join_oldpwd);
}

int	nb_cd_args(char **token)
{
	int	i;

	i = 1;
	while (token[i])
		i++;
	return (i - 1);
}

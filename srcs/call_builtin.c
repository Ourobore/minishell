/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:47:38 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/14 16:43:06 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	call_builtin(char **token, char **envp[])
{
	int	ret;

	ret = 0;
	if (ft_strcmp(token[0], "exit") == 0)
		ret = builtin_exit(token[0]);
	else if (ft_strcmp(token[0], "echo") == 0)
		ret = builtin_echo(token);
	else if (ft_strcmp(token[0], "pwd") == 0)
		ret = builtin_pwd();
	else if (ft_strcmp(token[0], "cd") == 0)
		ret = builtin_cd(token, envp);
	else if (ft_strcmp(token[0], "env") == 0)
		ret = builtin_env(*envp);
	else if (ft_strcmp(token[0], "export") == 0)
		ret = builtin_export(token, envp);
	else if (ft_strcmp(token[0], "unset") == 0)
		ret = builtin_unset(token, envp);
	return (ret);
}

void	call_builtin_pipe(char ***pipeline, int i, char *envp[])
{
	int	ret;

	ret = 0;
	if (ft_strcmp(pipeline[i][0], "exit") == 0)
		ret = builtin_exit(pipeline[i][0]);
	else if (ft_strcmp(pipeline[i][0], "echo") == 0)
		ret = builtin_echo(pipeline[i]);
	else if (ft_strcmp(pipeline[i][0], "pwd") == 0)
		ret = builtin_pwd();
	else if (ft_strcmp(pipeline[i][0], "cd") == 0)
		ret = builtin_cd(pipeline[i], &envp);
	else if (ft_strcmp(pipeline[i][0], "env") == 0)
		ret = builtin_env(envp);
	else if (ft_strcmp(pipeline[i][0], "export") == 0)
		ret = builtin_export(pipeline[i], &envp);
	else if (ft_strcmp(pipeline[i][0], "unset") == 0)
		ret = builtin_unset(pipeline[i], &envp);
	i = 0;
	free_double_array(envp);
	free_pipeline(pipeline);
	exit(ret);
}

int	is_builtin(char **token)
{
	if (ft_strcmp(token[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(token[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(token[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(token[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(token[0], "env") == 0)
		return (1);
	else if (ft_strcmp(token[0], "export") == 0)
		return (1);
	else if (ft_strcmp(token[0], "unset") == 0)
		return (1);
	else
		return (0);
}

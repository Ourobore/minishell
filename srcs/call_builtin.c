/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:47:38 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/11 15:20:20 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	call_builtin(char **token, char **envp[])
{
	int	ret;

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
	else
		exec_command(token, *envp);
	printf("ret: %d\n", ret);
	return (ret);
}

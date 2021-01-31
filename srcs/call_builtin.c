/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:47:38 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/30 10:23:52 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	call_builtin(char **token, char **envp[])
{
	int	ret;

	ret = -1; //ret = -1 and ret-- ?
	//if (ft_strcmp(token[0], "exit") == 0 && ret++)
	//	builtin_exit()
	if (ft_strcmp(token[0], "echo") == 0 && ret++)
		builtin_echo(token);
	if (ft_strcmp(token[0], "pwd") == 0 && ret++)
		builtin_pwd();
	if (ft_strcmp(token[0], "cd") == 0 && ret++)
		builtin_cd(token, envp);
	if (ft_strcmp(token[0], "env") == 0 && ret++)
		builtin_env(*envp);
	if (ft_strcmp(token[0], "export") == 0 && ret++)
		builtin_export(token, envp);
	if (ft_strcmp(token[0], "unset") == 0 && ret++)
		builtin_unset(token, envp);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:09:16 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/16 16:35:47 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	call_builtin(char **token)
{
	int	ret;

	ret = -1;
	//if (ft_strcmp(token[0], "exit") == 0 && ret++)
		//builtin_exit
	if (ft_strcmp(token[0], "echo") == 0 && ret++)
		builtin_echo(token);
	if (ft_strcmp(token[0], "pwd") == 0 && ret++)
		builtin_pwd(token);
	return (ret);
}

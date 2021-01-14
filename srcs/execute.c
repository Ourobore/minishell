/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:09:16 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/14 19:00:52 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	call_builtin(char **token)
{
	int	ret;

	ret = -1;
	if (ft_strcmp(token[0], "echo") == 0 && ret++)
		builtin_echo(token);
	return (ret);
}

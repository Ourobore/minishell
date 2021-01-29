/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 10:06:00 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/29 11:23:56 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tokenization(char *line, char **envp[])
{
	int		i;
	char	**cmd_split;
	char	**tokens;

	i = 0;
	//check characters and then call split by priority?
	cmd_split = ft_split(line, ';');
	//print_export(alphabetically_sort_env(*envp));
	while (cmd_split[i])
	{
		tokens = ft_split(cmd_split[i], ' '); //lexer?
		//verif tokens
		call_builtin(tokens, envp);
		free_double_array(tokens);
		i++;
	}
	free_double_array(cmd_split);
	return (0);
}

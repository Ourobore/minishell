/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:47:55 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/16 17:17:33 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	int		i;
	int		loop;
	char	*line;
	char	**tokens;
	char	**cmd_split;

	loop = 1;
	while (loop > 0)
	{
		i = 0;
		loop = prompt_line(&line);
		//split and loop in file tokenization.c ?
		cmd_split = ft_split(line, ';');
		while (cmd_split[i])
		{
			tokens = ft_split(cmd_split[i], ' '); //lexer?
			call_builtin(tokens);
			for (int y = 0; tokens[y]; y++)
				free(tokens[y]);
			free(tokens);
			free(cmd_split[i]);
			i++;
		}
		free(line);
		free(cmd_split);
	}
	//Free function
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:47:55 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/14 19:02:15 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	int		loop;
	char	*line;
	char	**split;

	loop = 1;
	while (loop > 0)
	{
		loop = prompt_line(&line);
		//split and loop in file tokenization.c ?
		//To do: split on ';' then loop with split on ' '
		split = ft_split(line, ' '); //lexer?
		call_builtin(split);
		/*
		for(int i = 0; split[i]; i++)
		{
			//To do:
			ft_putstr_fd(split[i], stdout);
			ft_putchar_fd('\n', stdout);
		}
		*/
		for (int i = 0; split[i]; i++)
			free(split[i]);
		free(split);
		free(line);
	}
	//Free function
}

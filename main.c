/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:47:55 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/28 11:29:17 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		prompt_loop;
	char	*line;/*
	char	**tokens;
	char	**cmd_split;
	int		*status;
	int		baby;*/
	

	prompt_loop = 1;
	argc = argc;
	argv = argv;
	/*
	printf("argc: %d\n", argc);
	for (int i = 0; argv[i]; i++)
	{
		printf("argv: %s\n", argv[i]);
	}
	for (int i = 0; envp[i]; i++)
	{
		printf("variable: %s\n", envp[i]);
	}
	*/
	while (prompt_loop > 0)
	{
		prompt_line(&line);
		prompt_loop = builtin_exit(line);
		tokenization(line, envp);
		/*
		//split and loop in file tokenization.c ?
		cmd_split = ft_split(line, ';');
		while (cmd_split[i])
		{
			tokens = ft_split(cmd_split[i], ' '); //lexer?
			call_builtin(tokens);
			free_double_array(tokens);
			i++;
		}
		free_double_array(cmd_split);
		*/
		free(line);
	}
	//Free function
}

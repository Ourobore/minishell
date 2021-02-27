/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:47:55 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/23 20:42:18 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char *envp[])
{
	int		prompt_loop;
	char	*line;
	char	**envp_copy;

	argc = argc;
	argv = argv;
	prompt_loop = 0;
	envp_copy = copy_envp(envp);

/*
	t_cmd *cmd = ft_calloc(sizeof(*cmd), 1);
	t_cmd *save = cmd;
	add_cmd(&cmd);
	cmd->ret = 42;
	cmd = cmd->next;
	add_cmd(&cmd);
	cmd->ret = 69;
	cmd = cmd->next;
	add_cmd(&cmd);
	cmd->ret = 789;
	printf("length list: [%d]\n", get_length_list(save));
	while (save->next != NULL)
	{
		printf("ret: %d\n", save->ret);
		save = save->next;
	}
*/

	if (!envp_copy)
		return (1);
	while (prompt_loop != -1 && prompt_loop != 255)
	{
		//printf("in prompt_loop\n");
		line = prompt_line();
		if (line == NULL)
		{
			printf("LINE EQUAL NULL\n");
			return (1);
		}
		if (verify_quotes(line) == 1)
		{
			ft_putendl_fd("No multilines", STDERR);
			continue;
		}
		prompt_loop = parse_line(line, &envp);
		//int test = is_in_line("\"ls\"", "ls");
		//printf("test: %d\n", test);
		//printf("in quote: %d\n", is_in_quotes(line, is_in_line(line, "ls")));
		//prompt_loop = tokenization(line, &envp_copy);
		//free(line);
	}
	free_double_array(envp_copy);
	if (prompt_loop == -1 || prompt_loop == 255)
	{
		//printf("in exit child\n");
		exit(-1);
	}
	//Free function
	//wait(NULL);
	printf("exit succes\n");
	exit(EXIT_SUCCESS);
	//return (0);
}

char	**copy_envp(char *envp[])
{
	int		i;
	int		length;
	char	**copy;

	length = get_length_double_array(envp);
	copy = NULL;
	copy = ft_calloc(sizeof(char*), length + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	return (copy);
}

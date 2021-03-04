/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:47:55 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/04 13:15:22 by lchapren         ###   ########.fr       */
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
	
	tgetent(NULL, get_token_value_in_envp("TERM", envp_copy));
	if (!envp_copy)
		return (1);
	while (prompt_loop != -1 && prompt_loop != 255)
	{
		//printf("in prompt_loop\n");
		line = prompt_line();
		char *cl_cap = tgetstr("cl", NULL);
		tputs (cl_cap, 1, putchar);
		if (line == NULL)
		{
			printf("LINE EQUAL NULL\n");
			return (1);
		}
		//if (verify_quotes(line) == 1)
		//{
		//	ft_putendl_fd("No multilines", STDERR);
		//	continue;
		//}
		prompt_loop = execution_loop(line, &envp_copy);
		free(line);
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
}

int	execution_loop(char *line, char **envp[])
{
	t_cmd	*head;
	int		i;
	int		exit_status;

	i = 0;
	exit_status = 1;
	while (i != -1 && line && line[i])
	{
		head = ft_calloc(sizeof(*head), 1);
		allocate_list(&head);
		i = parse_line(line, &head, i, *envp);
		if (i != -1)
			exit_status = call_builtin_or_pipe(head, line, envp);
		//close redirs
		free_command_list(head);
	}
	return (exit_status);
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

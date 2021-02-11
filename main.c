/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:47:55 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/11 16:49:33 by lchapren         ###   ########.fr       */
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
	int i = 0;
	int pipe_fd[2];
	int input_fd = 0;
	int	child_process;
	char *cat[] = {"/bin/cat", "main.c", NULL};
	char *grep[] = {"/bin/grep", "include", NULL};
	char *wc[] = {"/usr/bin/wc", NULL};
	char *less[] = {"/usr/bin/less", NULL};
	char **cmd[] = {cat, grep, wc, less, NULL};

	while (cmd[i] != NULL)
	{
		pipe(pipe_fd);
		child_process = fork();
		if (child_process == -1)
			exit(EXIT_FAILURE);
		if (child_process == 0)
		{
			dup2(input_fd, 0);
			if (cmd[i + 1] != NULL)
				dup2(pipe_fd[1], 1);
			close(pipe_fd[0]);
			call_builtin(cmd[i], &envp);
			//execve((cmd[i][0]), cmd[i], envp);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
			close(pipe_fd[1]);
			input_fd = pipe_fd[0];
			i++;
		}
	}
*/
	if (!envp_copy)
		return (1) ;
	while (prompt_loop != -1 && prompt_loop != 255)
	{
		//printf("in prompt_loop\n");
		prompt_line(&line);
		prompt_loop = tokenization(line, &envp_copy);
		//printf("prompt_loop: %d\n", prompt_loop);
		//prompt_loop = builtin_exit(line);
		//if (prompt_loop == 0)
		//	break ;
		//tokenization(line, &envp_copy);
		free(line);
	}
	free_double_array(envp_copy);
	if (prompt_loop == -1)
		exit(-1);
	//Free function
	//wait(NULL);
	printf("exit succes\n");
	exit(EXIT_SUCCESS);
	//return (0);
}

char **copy_envp(char *envp[])
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

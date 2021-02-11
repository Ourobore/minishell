/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 22:51:15 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/11 16:49:51 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_pipeline(char ***pipeline, char **envp[])
{
	int i = 0;
	int pipe_fd[2];
	int input_fd = 0;
	int	child_process;
	int	exit_status;
	
	exit_status = 0;
	while (pipeline[i] != NULL && (exit_status != -1 && exit_status != 255))
	{
		pipe(pipe_fd);
		child_process = fork();
		if (child_process == -1)
			exit(EXIT_FAILURE);
		if (child_process == 0)
		{
			dup2(input_fd, 0);
			if (pipeline[i + 1] != NULL)
				dup2(pipe_fd[1], 1);
			close(pipe_fd[0]);
			exit_status = call_builtin(pipeline[i], envp);
			//function to free pipeline
			//exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(child_process, &exit_status, 0);
			exit_status = WEXITSTATUS(exit_status);
			printf("exit_status: %d\n", exit_status);
			close(pipe_fd[1]);
			input_fd = pipe_fd[0];
			i++;
		}
	}
	return (exit_status);
}

void	open_pipe_fd(int **pipe_fd)
{
	if (pipe(*pipe_fd) == -1)
	{
		strerror(errno);
		exit(EXIT_FAILURE);
	}
}

void	close_pipe_fd(int *pipe_fd)
{
	if (close(pipe_fd[FDREAD]) == -1)
	{
		printf("in close error\n");
		strerror(errno);
		exit(EXIT_FAILURE);
	}
	if (close(pipe_fd[FDWRITE]) == -1)
	{
		printf("in close error\n");
		strerror(errno);
		exit(EXIT_FAILURE);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 22:51:15 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/14 16:53:16 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_pipeline(char ***pipeline, char **command_line, char *envp[])
{
	int	i;
	int	pipe_fd[2];
	int	input_fd;
	int	child_process;
	int	exit_status;

	i = 0;
	input_fd = 0;
	exit_status = 0;
	while (pipeline[i] != NULL && exit_status != -1 && exit_status != 255)
	{
		piping_and_forking(&(pipe_fd), &child_process);
		if (child_process == 0)
		{
			dup2(input_fd, STDIN);
			if (pipeline[i + 1] != NULL)
				dup2(pipe_fd[FDWRITE], STDOUT);
			close(pipe_fd[FDREAD]);
			exit_status = exec_command(pipeline[i], envp);
			free_double_array(command_line);
			call_builtin_pipe(pipeline, i, envp);
		}
		else
		{
			waitpid(child_process, &exit_status, 0);
			exit_status = WEXITSTATUS(exit_status);
			close(pipe_fd[FDWRITE]);
			input_fd = pipe_fd[FDREAD];
			i++;
		}
	}
	return (exit_status);
}

void	piping_and_forking(int (*pipe_fd)[2], int *child_process)
{
	if (pipe(*pipe_fd) == -1)
	{
		ft_putendl_fd(strerror(errno), STDERR);
		exit(EXIT_FAILURE);
	}
	*child_process = fork();
	if (*child_process == -1)
	{
		ft_putendl_fd(strerror(errno), STDERR);
		exit(EXIT_FAILURE);
	}
}

int	get_pipes_number(char *command_line)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while (command_line[i])
	{
		if (command_line[i] == '|')
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

int	get_length_pipeline(char ***pipeline)
{
	int	i;

	i = 0;
	while (pipeline[i])
		i++;
	return (i);
}

void	free_pipeline(char ***pipeline)
{
	int	i;

	i = 0;
	while (pipeline[i])
	{
		free_double_array(pipeline[i]);
		i++;
	}
	free(pipeline);
}

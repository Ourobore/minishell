/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 22:51:15 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/27 13:23:09 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_pipeline(t_cmd *head, char *buffer, char *envp[])
{
	int	pipe_fd[2];
	int	input_fd;
	int	child_process;
	int	exit_status;

	input_fd = 0;
	exit_status = 0;
	t_cmd *verif;
	verif = head;
	int count = 0;
	//int	save_out;
	//int	save_in;
	while (verif != NULL)
	{
		count++;
		verif = verif->next;
	}
	//printf("PIPE LENGTH: [%d]\n", count);
	while (head != NULL && exit_status != -1 && exit_status != 255)
	{
		//printf("\n---in pipe redir in: [%d]---\n", head->redir_in);
		//printf("---in pipe redir out: [%d]---\n", head->redir_out);
		//printf("INPUT FD: [%d]\n", input_fd);
		//printf("---[NEW TOKEN]---\n");
		//for (int k = 0; head->token[k]; k++)
		//	printf("FOR TOKEN: %s\n", head->token[k]);
		pipes_forks_redirs(head, &input_fd, &(pipe_fd), &child_process);
		if (child_process == 0)
		{
			if (head->redir_in != -1)
				input_fd = head->redir_in;
			dup2(input_fd, STDIN);
			if (head->redir_out != -1)
				pipe_fd[FDWRITE] = head->redir_out;
			if (head->next != NULL || head->redir_out != -1)
				dup2(pipe_fd[FDWRITE], STDOUT);
			//if (head->redir_out != -1)
			//	dup2(STDOUT, head->redir_out);
			close(pipe_fd[FDREAD]);
			exit_status = exec_command(head->token, envp);
			free(buffer);
			call_builtin_pipe(head, envp);
		}
		else
		{
			waitpid(child_process, &exit_status, 0);
			//printf("PROCESS: [%d]\n", child_process);
			//printf("INPUT_FD: [%d]\tPIPE READ: [%d]\tPIPE WRITE[%d]\n", input_fd, pipe_fd[FDREAD], pipe_fd[FDWRITE]);
			exit_status = WEXITSTATUS(exit_status);
			if (input_fd != 0) // important to avoid fd leak from input_fd = FDREAD
				close(input_fd);
			close(pipe_fd[FDWRITE]);
			//if ()
			//if (pipe_fd[FDREAD] != head->redir_out)
			input_fd = pipe_fd[FDREAD];
			//else
			//	input_fd = 0;
			head = head->next;
		}
	}
	close(pipe_fd[FDREAD]);
	close(pipe_fd[FDWRITE]);
	close(input_fd);
	return (exit_status);
}

void	pipes_forks_redirs(t_cmd *head, int *input_fd, int (*pipe_fd)[2], int *child_process)
{
	if (pipe(*pipe_fd) == -1)
	{
		ft_putendl_fd(strerror(errno), STDERR);
		exit(EXIT_FAILURE);
	}
	head=head;
	input_fd=input_fd;
	//if (head->redir_in != -1)
	//	*input_fd = head->redir_in;
	//if (head->redir_out != -1)
	//	(*pipe_fd)[FDWRITE] = head->redir_out;
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

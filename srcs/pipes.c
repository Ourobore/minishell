/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 22:51:15 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/16 18:49:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_pipeline(t_cmd *head, char *envp[])
{
	t_cmd	*cmd;
	int		*pipefd;
	int		nb_pipes;
	int		command_number;
	int		child_process;

	cmd = head;
	nb_pipes = get_length_list(head) - 1;
	pipefd = ft_calloc(sizeof(int), nb_pipes * 2);
	if (!pipefd)
		return (-1);
	open_close_pipes(pipefd, nb_pipes, 1);
	command_number = 0;
	while (cmd != NULL)
	{
		open_redir_hub(&cmd);
		child_process = fork();
		if (child_process == 0)
		{
			child_pipe_redir(cmd, pipefd, command_number, nb_pipes);
			child_exec(cmd, head, envp);
		}
		cmd = cmd->next;
		command_number++;
	}
	open_close_pipes(pipefd, nb_pipes, 2);
	return (get_child_status(child_process, nb_pipes));
}

void	child_pipe_redir(t_cmd *head, int *pipefd, int cmd_num, int nb_pipes)
{
	if (head->redir_in != -1)
		dup2(head->redir_in, STDIN);
	else if (cmd_num != 0)
		dup2(pipefd[(cmd_num - 1) * 2], STDIN);
	if (head->redir_out != -1)
		dup2(head->redir_out, STDOUT);
	else if (head->next)
		dup2(pipefd[cmd_num * 2 + 1], STDOUT);
	open_close_pipes(pipefd, nb_pipes, 2);
}

void	child_exec(t_cmd *cmd, t_cmd *head, char *envp[])
{
	call_builtin_pipe(cmd, envp);
	exec_command(cmd->token, envp);
	ft_putendl_fd(MINISHELL"Executable does not exists", 2);
	free_double_array(envp);
	free_command_list(head);
	//error handling if exec doesn't exists
	exit(EXIT_FAILURE);
}

int	get_child_status(int child_process, int nb_pipes)
{
	int	i;
	int	status;

	waitpid(child_process, &status, 0);
	if (WIFSIGNALED(status))
		printf("in prout\n");
	exit_value = WEXITSTATUS(status);
	i = 0;
	while (i < nb_pipes + 1)
	{
		wait(&status);
		i++;
	}
	return (exit_value);
}

void	open_close_pipes(int *pipefd, int nb_pipes, int mode)
{
	int	i;

	i = 0;
	if (mode == 1)
	{
		while (i < nb_pipes)
		{
			pipe(pipefd + 2 * i);
			i++;
		}
	}
	if (mode == 2)
	{
		while (i < nb_pipes * 2)
		{
			close(pipefd[i]);
			i++;
		}
		free(pipefd);
	}
}

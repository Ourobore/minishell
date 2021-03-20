/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 22:51:15 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/20 12:42:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		exec_pipeline(t_cmd *head, char *envp[])
{
	int		*pipefd;
	int		nb_pipes;
	int		child_process;

	child_process = 0;
	nb_pipes = get_length_list(head) - 1;
	pipefd = ft_calloc(sizeof(int), nb_pipes * 2);
	if (!pipefd)
		return (-2);
	open_close_pipes(pipefd, nb_pipes, 1);
	child_process = pipe_loop(head, &pipefd, envp);
	open_close_pipes(pipefd, nb_pipes, 2);
	if (child_process == -1)
	{
		g_shell.exit_value = 1;
		return (1);
	}
	return (get_child_status(child_process, nb_pipes));
}

int		pipe_loop(t_cmd *head, int **pipefd, char *envp[])
{
	t_cmd	*cmd;
	int		nb_pipes;
	int		command_number;
	int		child_process;

	nb_pipes = get_length_list(head) - 1;
	command_number = 0;
	cmd = head;
	child_process = -1;
	while (cmd != NULL)
	{
		if (open_redir_hub(&cmd))
		{
			child_process = fork();
			g_shell.in_fork = 1;
			if (child_process == 0)
			{
				child_pipe_redir(cmd, *pipefd, command_number, nb_pipes);
				child_exec(cmd, envp);
			}
		}
		cmd = cmd->next;
		command_number++;
	}
	return (child_process);
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

void	child_exec(t_cmd *cmd, char *envp[])
{
	if (cmd->token[0])
	{
		call_builtin_pipe(cmd, envp);
		exec_command(cmd->token, envp);
		ft_putstr_fd(MINISHELL, 2);
		ft_putstr_fd(cmd->token[0], 2);
		ft_putendl_fd(": command not found", 2);
	}
	free_shell_data(1);
	exit(127);
}

int		get_child_status(int child_process, int nb_pipes)
{
	int	i;
	int	status;

	waitpid(child_process, &status, 0);
	if (WIFSIGNALED(status))
		g_shell.exit_value = 128 + WTERMSIG(status);
	else
		g_shell.exit_value = WEXITSTATUS(status);
	if (g_shell.exit_value == 131)
		ft_putendl_fd("Quit (core dumped)", 2);
	i = 0;
	while (i < nb_pipes + 1)
	{
		wait(&status);
		i++;
	}
	g_shell.in_fork = 0;
	return (g_shell.exit_value);
}

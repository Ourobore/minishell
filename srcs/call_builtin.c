/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:47:38 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/16 18:48:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	call_builtin_or_pipe(t_lst *cmd_line, char **envp[])
{
	int	length;
	int	exit_status;

	exit_status = 0;
	while (cmd_line != NULL)
	{
		length = get_length_list(cmd_line->cmd);
		if (length == 1 && is_builtin(cmd_line->cmd->token))
			exit_status = call_builtin(cmd_line->cmd, envp);
		else
			exit_status = exec_pipeline(cmd_line->cmd, *envp);
		cmd_line = cmd_line->next;
	}
	return (exit_status);
}

int	call_builtin(t_cmd *cmd, char **envp[])
{
	int	ret;
	int	save_out;
	int	save_in;

	ret = 0;
	open_redir_hub(&cmd);
	builtin_redir(cmd, &save_in, &save_out, 1);
	if (ft_strcmp(cmd->token[0], "exit") == 0)
		ret = builtin_exit(cmd->token[0]);
	else if (ft_strcmp(cmd->token[0], "echo") == 0)
		ret = builtin_echo(cmd->token);
	else if (ft_strcmp(cmd->token[0], "pwd") == 0)
		ret = builtin_pwd();
	else if (ft_strcmp(cmd->token[0], "cd") == 0)
		ret = builtin_cd(cmd->token, envp);
	else if (ft_strcmp(cmd->token[0], "env") == 0)
		ret = builtin_env(*envp);
	else if (ft_strcmp(cmd->token[0], "export") == 0)
		ret = builtin_export(cmd->token, envp);
	else if (ft_strcmp(cmd->token[0], "unset") == 0)
		ret = builtin_unset(cmd->token, envp);
	builtin_redir(cmd, &save_in, &save_out, 2);
	return (ret);
}

void	builtin_redir(t_cmd *cmd, int *save_in, int *save_out, int mode)
{
	if (cmd->redir_in != -1 && mode == 1)
	{
		*save_in = dup(STDIN);
		dup2(cmd->redir_in, STDIN);
	}
	if (cmd->redir_out != -1 && mode == 1)
	{
		*save_out = dup(STDOUT);
		dup2(cmd->redir_out, STDOUT);
	}
	if (cmd->redir_in != -1 && mode == 2)
	{
		dup2(*save_in, STDIN);
		close(*save_in);
	}
	if (cmd->redir_out != -1 && mode == 2)
	{
		dup2(*save_out, STDOUT);
		close(*save_out);
	}
}

void	call_builtin_pipe(t_cmd *cmd, char *envp[])
{
	int	ret;

	ret = -2;
	if (ft_strcmp(cmd->token[0], "exit") == 0)
		ret = builtin_exit(cmd->token[0]);
	else if (ft_strcmp(cmd->token[0], "echo") == 0)
		ret = builtin_echo(cmd->token);
	else if (ft_strcmp(cmd->token[0], "pwd") == 0)
		ret = builtin_pwd();
	else if (ft_strcmp(cmd->token[0], "cd") == 0)
		ret = builtin_cd(cmd->token, &envp);
	else if (ft_strcmp(cmd->token[0], "env") == 0)
		ret = builtin_env(envp);
	else if (ft_strcmp(cmd->token[0], "export") == 0)
		ret = builtin_export(cmd->token, &envp);
	else if (ft_strcmp(cmd->token[0], "unset") == 0)
		ret = builtin_unset(cmd->token, &envp);
	if (ret != -2)
	{
		free_double_array(envp);
		free_command_list(cmd);
		exit(ret);
	}
}

int	is_builtin(char **token)
{
	if (ft_strcmp(token[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(token[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(token[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(token[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(token[0], "env") == 0)
		return (1);
	else if (ft_strcmp(token[0], "export") == 0)
		return (1);
	else if (ft_strcmp(token[0], "unset") == 0)
		return (1);
	else
		return (0);
}

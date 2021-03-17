/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:47:38 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/17 18:18:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	call_builtin_or_pipe(t_lst *cmd_line, char **envp[])
{
	int		length;
	int		exit_status;
	t_lst	*tmp;

	tmp = cmd_line;
	exit_status = 0;
	while (tmp != NULL)
	{
		length = get_length_list(tmp->cmd);
		if (length == 1 && is_builtin(tmp->cmd->token))
			exit_status = call_builtin(tmp->cmd, cmd_line, envp);
		else
			exit_status = exec_pipeline(tmp->cmd, cmd_line, *envp);
		tmp = tmp->next;
	}
	return (exit_status);
}

int	call_builtin(t_cmd *cmd, t_lst *cmd_line, char **envp[])
{
	int	ret;
	int	save_out;
	int	save_in;

	ret = 0;
	open_redir_hub(&cmd);
	builtin_redir(cmd, &save_in, &save_out, 1);
	if (ft_strcmp(cmd->token[0], "exit") == 0)
		ret = builtin_exit(cmd->token, cmd_line, *envp);
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
	g_exit_value = ret;
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

void	call_builtin_pipe(t_cmd *cmd, t_lst *cmd_line, char *envp[])
{
	int	ret;

	ret = -2;
	if (ft_strcmp(cmd->token[0], "exit") == 0)
		ret = builtin_exit(cmd->token, cmd_line, envp);
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
		free_command_line(cmd_line);
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

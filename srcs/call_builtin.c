/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 09:47:38 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/25 14:06:26 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	call_builtin_or_pipe(t_cmd *head, char *buffer, char **envp[])
{
	int	length;

	length = get_length_list(head);
	if (length == 0 && is_builtin(head->token))
		head->ret = call_builtin(head, envp);
	else
		exec_pipeline(head, buffer, *envp);
	return (head->ret);
}

int	call_builtin(t_cmd *head, char **envp[])
{
	int	ret;
	//int	save_out;
	//int save_in;

	ret = 0;
	for (int i = 0; head->token[i]; i++)
		printf("TOKEN: %s\n", head->token[i]);
	printf("FD: [%d]\n", head->redir_out);
	/*
	if (head->redir_in != -1)
	{
		save_in = dup(STDIN);
		dup2(head->redir_in, STDIN);
		close(head->redir_in);
	}
	if (head->redir_out != -1)
	{
		save_out = dup(STDOUT);
		dup2(head->redir_out, STDOUT);
		close(head->redir_out);
	}*/
	if (ft_strcmp(head->token[0], "exit") == 0)
		ret = builtin_exit(head->token[0]);
	else if (ft_strcmp(head->token[0], "echo") == 0)
		ret = builtin_echo(head->token);
	else if (ft_strcmp(head->token[0], "pwd") == 0)
		ret = builtin_pwd();
	else if (ft_strcmp(head->token[0], "cd") == 0)
		ret = builtin_cd(head->token, envp);
	else if (ft_strcmp(head->token[0], "env") == 0)
		ret = builtin_env(*envp);
	else if (ft_strcmp(head->token[0], "export") == 0)
		ret = builtin_export(head->token, envp);
	else if (ft_strcmp(head->token[0], "unset") == 0)
		ret = builtin_unset(head->token, envp);
	/*if (head->redir_in != -1)
		dup2(save_in, STDIN);
	if (head->redir_out != -1)
		dup2(save_out, STDOUT);*/
	return (ret);
}

void	call_builtin_pipe(t_cmd *cmd, char *envp[])
{
	int	ret;
	int	save_in;
	int	save_out;

	ret = -1;
	printf("In builtin pipe\n");
	if (cmd->redir_in != -1)
	{
		save_in = dup(STDIN);
		dup2(cmd->redir_in, STDIN);
		close(cmd->redir_in);
	}
	if (cmd->redir_out != -1)
	{
		save_out = dup(STDOUT);
		dup2(cmd->redir_out, STDOUT);
		close(cmd->redir_out);
	}
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
	if (cmd->redir_in != -1)
		dup2(save_in, STDIN);
	if (cmd->redir_out != -1)
	{
		dup2(save_out, STDOUT);
		close(save_out);
	}
	
	//if (ret != -1)
	//	free_double_array(envp);
	exit(ret);
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

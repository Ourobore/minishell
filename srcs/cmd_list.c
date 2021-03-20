/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 09:37:10 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/20 07:06:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_cmd(t_cmd **cmd)
{
	t_cmd	*new;

	if (!cmd)
		return (0);
	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return (0);
	new = allocate_list(new);
	if (!new)
	{
		if (new)
			free(new);
		return (0);
	}
	if (!*cmd)
	{
		*cmd = new;
		return (1);
	}
	while ((*cmd)->next)
		*cmd = (*cmd)->next;
	(*cmd)->next = new;
	return (1);
}
/*
t_lst	*add_command_line(t_lst *cmd_line)
{
	t_cmd	*new_cmd;
	t_lst	*new_line;
	t_lst	*tmp;

	new_cmd = ft_calloc(sizeof(*new_cmd), 1);
	new_cmd = allocate_list(new_cmd);
	new_line = ft_calloc(sizeof(*new_line), 1);
	if (!new_cmd || !new_line)
		return (NULL);
	new_line->cmd = new_cmd;
	new_line->line = NULL;
	new_line->envp_copy = NULL;
	new_line->in_fork = 0;
	new_line->exit_value = -1;
	new_line->next = NULL;
	if (!cmd_line)
		cmd_line = new_line;
	else
	{
		tmp = cmd_line;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_line;
	}
	return (cmd_line);
}
*/
t_cmd	*allocate_list(t_cmd *cmd)
{
	cmd->token = ft_calloc(sizeof(char *), 1);
	if (!cmd->token)
		return (NULL);
	cmd->redir_file = ft_calloc(sizeof(char *), 1);
	if (!cmd->redir_file)
		return (NULL);
	cmd->redir_in = -1;
	cmd->redir_out = -1;
	cmd->next = NULL;
	return (cmd);
}

int	get_length_list(t_cmd *head)
{
	int	i;

	i = 0;
	while (head != NULL)
	{
		head = head->next;
		i++;
	}
	return (i);
}

void	free_command_list(t_cmd *head)
{
	t_cmd	*tmp;

	while (head != NULL)
	{
		if (head->token)
		{
			free_double_array(head->token);
			head->token = NULL;
		}
		if (head->redir_file)
		{
			free_double_array(head->redir_file);
			head->redir_file = NULL;
		}
		if (head->redir_in != -1 && head->redir_out != -2)
			close(head->redir_in);
		if (head->redir_out != -1 && head->redir_out != -2)
			close(head->redir_out);
		tmp = head;
		head = head->next;
		free(tmp);
	}
	head = NULL;
}

void	free_shell_data(int mode)
{
	if (mode == 1)
	{
		free_double_array(g_shell.envp_copy);
		if (g_shell.line)
		{
			free(g_shell.line);
			g_shell.line = NULL;
		}
		g_shell.envp_copy = NULL;
	}
	if (g_shell.cmd)
		free_command_list(g_shell.cmd);
	g_shell.cmd = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 09:37:10 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/23 16:29:30 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_cmd(t_cmd **cmd)
{
	t_cmd	*new;

	new = ft_calloc(sizeof(*new), 1);
	if (!new)
		return (0);
	if (!allocate_list(&new))
		return (0);
	if (!cmd)
		return (0);
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

int	get_length_list(t_cmd *head)
{
	int	i;

	i = 0;
	while (head->next != NULL)
	{
		head = head->next;
		i++;
	}
	return (i);
}

int	allocate_list(t_cmd **cmd)
{
	(*cmd)->token = ft_calloc(sizeof(char*), 1); //maybe redondant
	if (!(*cmd)->token)
		return (0);
	(*cmd)->redir_in = -1;
	(*cmd)->redir_out = -1;
	(*cmd)->ret = 0;
	(*cmd)->next = NULL;
	return (1);
}

void	free_command_list(t_cmd *head)
{
	t_cmd	*tmp;

	while (head != NULL)
	{
		free_double_array(head->token);
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

/*
void	get_pipeline(t_cmd **cmd, char *command_line)
{

}

int	is_in_quotes(char *line, char *token)
{
	int	i;
	int in_simple;
	int	in_double;

	i = 0;
	in_simple = 0;
	in_double = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			in_simple = !in_simple;
		if (line[i] == '\"')
			in_double = !in_double;
	}
}
*/
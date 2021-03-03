/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 09:09:48 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/02 10:40:25 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_redirection(t_cmd *head, char *line, int *i , char *buffer)
{
	int	j;
	int	redir_type;
	
	if (line[*i] == '<')
		redir_type = 1;
	if (line[*i] == '>')
	{
		if (line[(*i) + 1] == '>')
		{
			redir_type = 3;
			(*i)++;
		}
		else
			redir_type = 2;
	}
	(*i)++;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	j = 0;
	while (line[*i] && !is_special_character(line[*i]))
	{
		//printf("LINE[I]: %c\tI{%d}\n", line[*i], *i);
		buffer[j++] = line[(*i)++];
	}
	if (ft_strlen(buffer) == 0)
		ft_putendl_fd("Syntax error near '>'", 2);
		//free everything
	(*i)--;
	int	fd;
	if (redir_type == 1)
	{
		fd = open(buffer, O_RDONLY);
		if (fd == -1)
			ft_putendl_fd(strerror(errno), STDERR);
		else
		{
			if (head->redir_in != -1)
				close(head->redir_in);
			head->redir_in = fd;
		}
	}
	if (redir_type == 2)
	{
		fd = open(buffer, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (fd == -1)
			ft_putendl_fd(strerror(errno), STDERR);
		else
		{
			if (head->redir_out != -1)
				close(head->redir_out);
			head->redir_out = fd;
		}
	}
	if (redir_type == 3)
	{
		fd = open(buffer, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (fd == -1)
			ft_putendl_fd(strerror(errno), STDERR);
		else
		{
			if (head->redir_out != -1)
				close(head->redir_out);
			head->redir_out = fd;
		}
	}
	ft_bzero(buffer, ft_strlen(buffer));
	return (fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 09:09:48 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/18 18:28:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_redir_name(char *line, int *i, char **buffer, char *envp[])
{
	int	redir_type;

	redir_type = get_redir_type(line, i, buffer);
	(*i)++;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	*buffer = get_next_token(line, i, *buffer, envp);
	if (((redir_type == 1 || redir_type == 2) && ft_strlen(*buffer) == 2) || (\
		redir_type == 3 && ft_strlen(*buffer) == 3))
	{
		if (redir_type == 1)
			print_syntax_error('<');
		else
			print_syntax_error('>');
		*i = -1;
	}
}

int	get_redir_type(char *line, int *i, char **buffer)
{
	buffer = buffer;
	if (line[*i] == '<')
	{
		(*buffer)[0] = '<';
		(*buffer)[1] = ' ';
		return (1);
	}
	if (line[*i] == '>')
	{
		if (line[(*i) + 1] && line[(*i) + 1] == '>')
		{
			(*i)++;
			(*buffer)[0] = '>';
			(*buffer)[1] = '>';
			(*buffer)[2] = ' ';
			return (3);
		}
		else
		{
			(*buffer)[0] = '>';
			(*buffer)[1] = ' ';
			return (2);
		}
	}
	return (0);
}

int	open_redir_hub(t_cmd **cmd)
{
	int		i;
	int		redir_type;
	int		error;
	char	*file;

	i = 0;
	error = 0;
	while (error != 1 && (*cmd)->redir_file[i])
	{
		file = (*cmd)->redir_file[i];
		if (file[0] == '<')
			redir_type = 1;
		else if (file[0] == '>')
		{
			if (file[1] == '>')
				redir_type = 3;
			else
				redir_type = 2;
		}
		if (redir_type == 1)
			error = open_redir_in(cmd, &file[2]);
		else if (redir_type == 2)
			error = open_redir_out(cmd, &file[2], redir_type);
		else if (redir_type == 3)
			error = open_redir_out(cmd, &file[3], redir_type);
		i++;
	}
	return (!error);
}

int	open_redir_in(t_cmd **cmd, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(MINISHELL, 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), STDERR);
		return (1);
	}
	else
	{
		if ((*cmd)->redir_in != -1)
			close((*cmd)->redir_in);
		(*cmd)->redir_in = fd;
		return (0);
	}
}

int	open_redir_out(t_cmd **cmd, char *file_name, int redir_type)
{
	int	fd;

	if (redir_type == 2)
		fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	else if (redir_type == 3)
		fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, \
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd == -1)
	{
		ft_putstr_fd(MINISHELL, 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), STDERR);
		return (1);
	}
	else
	{
		if ((*cmd)->redir_out != -1)
			close((*cmd)->redir_out);
		(*cmd)->redir_out = fd;
		return (0);
	}
}

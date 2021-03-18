/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:35:36 by user42            #+#    #+#             */
/*   Updated: 2021/03/18 19:18:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signal)
{
	(void)signal;
	ft_bzero(g_cmd_line->line, ft_strlen(g_cmd_line->line));
	printf("in_fork: %d\n", g_cmd_line->exit_value);
	if (!g_cmd_line->in_fork)
	{
		g_cmd_line->exit_value = 130;
		ft_putchar_fd('\n', 1);
		ft_putstr_fd("\033[1;33m"PROMPT"\033[0;0m", 1);
	}
}

void	sigquit_handler(int signal)
{
	(void)signal;
	
	if (!g_cmd_line->in_fork && g_cmd_line->line[0])
	{
		free(g_cmd_line->line);
		g_cmd_line->line = NULL;
	}
	//free_command_line(g_cmd_line, 2);
	//g_cmd_line = NULL;
	//exit(128 + signal);
}

char	*add_character(char *input, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (input[i])
		i++;
	str = malloc((i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (input[i])
	{
		str[i] = input[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = 0;
	free(input);
	return (str);
}

char	*get_line(char *line)
{
	int		ret;
	char	c;

	line = NULL;
	line = ft_calloc(sizeof(char), 1);
	if (!line)
		return (NULL);
	line[0] = 0;
	ret = read(0, &c, 1);
	if (ret == 0)
	{
		free(line);
		free_command_line(g_cmd_line, 2);
		ft_putendl_fd("exit", 2);
		exit(130);
	}
	while (c != '\n')
	{
		line = add_character(line, c);
		ret = read(0, &c, 1);
	}
	if (ret == -1 || line == NULL)
		return (NULL);
	return (line);
}
/*
char	*ft_cat(char *s, char c)
{
	int		i;
	char	*cat;

	i = 0;
	while (s[i] != 0)
		i++;
	cat = malloc(sizeof(*cat) * (i + 2));
	if (!cat)
		return (NULL);
	i = 0;
	while (s[i] != 0)
	{
		cat[i] = s[i];
		i++;
	}
	cat[i] = c;
	cat[i + 1] = 0;
	free(s);
	return (cat);
}

int	get_next_line(int fd, char **line)
{
	char	*cat;
	char	buf;
	int		ret;

	cat = malloc(sizeof(char) * 1);
	if (fd < 0 || !line || !cat)
		return (-1);
	cat[0] = 0;
	ret = read(fd, &buf, 1);
	while (ret != 0)
	{
		if (ret == -1)
			return (-1);
		if (buf == '\n')
			break ;
		cat = ft_cat(cat, buf);
		ret = read(fd, &buf, 1);
	}
	*line = cat;
	if (*line == NULL)
		ret = -1;
	return (ret);
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:35:36 by user42            #+#    #+#             */
/*   Updated: 2021/03/20 08:03:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signal)
{
	(void)signal;
	ft_bzero(g_shell.line, ft_strlen(g_shell.line));
	ft_putchar_fd('\n', 1);
	if (!g_shell.in_fork)
	{
		g_shell.exit_value = 130;
		ft_putstr_fd("\033[1;33m"PROMPT"\033[0;0m", 1);
	}
}

void	sigquit_handler(int signal)
{
	(void)signal;
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
		free_shell_data(1);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:47:55 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/20 10:39:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_shell;

int	main(int argc, char **argv, char *envp[])
{
	int		exit_status;

	(void)argc;
	(void)argv;
	initialize_data(envp);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
		ft_putstr_fd("\033[1;33m"PROMPT"\033[0;0m", 1);
		g_shell.line = get_line();
		exit_status = parsing_hub(g_shell.line, g_shell.envp_copy, 0);
		if (ft_strlen(g_shell.line) > 0 && exit_status >= 0)
			exit_status = parsing_hub(g_shell.line, g_shell.envp_copy, 1);
		if (g_shell.line)
		{
			free(g_shell.line);
			g_shell.line = NULL;
		}
		if (exit_status == -2)
		{
			ft_putendl_fd("Malloc allocation error. Exit", 2);
			free_shell_data(2);
			exit(1);
		}
	}
}

void	initialize_data(char *envp[])
{
	g_shell.cmd = NULL;
	g_shell.line = NULL;
	g_shell.envp_copy = copy_envp(envp);
	g_shell.in_fork = 0;
	g_shell.exit_value = 0;
}

char	**copy_envp(char *envp[])
{
	int		i;
	int		length;
	char	**copy;

	length = get_length_double_array(envp);
	copy = NULL;
	copy = ft_calloc(sizeof(char *), length + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	return (copy);
}

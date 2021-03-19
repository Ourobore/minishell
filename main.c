/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:47:55 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/19 12:04:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*g_cmd_line;

int	main(int argc, char **argv, char *envp[])
{
	int		exit_status;
	int		exit_value;
	char	**envp_copy;

	(void)argc;
	(void)argv;
	exit_value = 0;
	envp_copy = copy_envp(envp);
	while (1)
	{
		initialize_cmd_line(envp_copy, exit_value);
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
		ft_putstr_fd("\033[1;33m"PROMPT"\033[0;0m", 1);
		g_cmd_line->line = get_line(g_cmd_line->line);
		exit_status = execution_loop(g_cmd_line->line, g_cmd_line, &envp);
		if (exit_status == -2)
		{
			ft_putendl_fd("Malloc allocation error. Exit", 2);
			free_command_line(g_cmd_line, 2);
			exit(1);
		}
		exit_value = g_cmd_line->exit_value;
		free_command_line(g_cmd_line, 1);
	}
}

int	execution_loop(char *line, t_lst *cmd_line, char **envp[])
{
	int		exit_value;
	char	*bak_line;
	char	**bak_envp;
	int		exit_status;

	exit_status = 0;
	exit_status = parsing_hub(line, cmd_line, *envp, 1);
	if (ft_strlen(cmd_line->line) > 0 && exit_status >= 0)
	{
		exit_value = cmd_line->exit_value;
		bak_line = ft_strdup(line);
		bak_envp = copy_envp(*envp);
		free_command_line(cmd_line, 2);
		initialize_cmd_line(bak_envp, exit_value);
		cmd_line = g_cmd_line;
		cmd_line->line = bak_line;
		parsing_hub(cmd_line->line, cmd_line, *envp, 2);
	}
	return (exit_status);
}

void	initialize_cmd_line(char *envp_copy[], int exit_value)
{
	g_cmd_line = NULL;
	g_cmd_line = add_command_line(g_cmd_line);
	g_cmd_line->envp_copy = envp_copy;
	g_cmd_line->in_fork = 0;
	g_cmd_line->exit_value = exit_value;
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

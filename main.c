/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:47:55 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/17 18:04:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_value;

int	main(int argc, char **argv, char *envp[])
{
	int		prompt_loop;
	char	*line;
	char	**envp_copy;

	(void)argc;
	(void)argv;
	prompt_loop = 0;
	g_exit_value = 0;
	envp_copy = copy_envp(envp);
	while (prompt_loop != -2)
	{
		ft_putstr_fd("\033[1;33m"PROMPT"\033[0;0m", 1);
		get_next_line(0, &line);
		prompt_loop = execution_loop(line, &envp_copy);
	}
	free_double_array(envp_copy);
	exit(EXIT_SUCCESS);
}

int	execution_loop(char *line, char **envp[])
{
	t_lst	*cmd_line;
	int		length_line;
	int		exit_status;

	exit_status = 0;
	length_line = ft_strlen(line);
	cmd_line = NULL;
	cmd_line = add_command_line(cmd_line);
	exit_status = parsing_hub(line, &cmd_line, *envp);
	printf("EXIT_STATUS PARSING: [%d]\n", exit_status);
	free(line);
	//if (exit_status < 0) // if exit == -2 failed malloc 
	//	printf("error parsing\n");
	if (length_line > 0 && exit_status >= 0)
		exit_status = call_builtin_or_pipe(cmd_line, envp);
	printf("G_EXIT_VALUE: [%d]\n", g_exit_value);
	free_command_line(cmd_line);
	return (exit_status);
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

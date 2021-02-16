/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 10:06:00 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/15 14:46:08 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tokenization(char *line, char **envp[])
{
	int		i;
	int		exit_status;
	char	**command_line;
	char	***pipeline;

	i = 0;
	exit_status = 0;
	command_line = ft_split(line, ';');
	free(line);
	while (command_line[i] && (exit_status != -1 && exit_status != 255))
	{
		//verif tokens
		pipeline = create_pipeline(command_line[i], *envp);
		if (verify_pipeline(pipeline, command_line[i], *envp))
		{
			if (get_pipes_number(command_line[i]) == 0 && is_builtin(pipeline[0]))
				exit_status = call_builtin(pipeline[0], envp);
			else
				exit_status = exec_pipeline(pipeline, command_line, *envp);
		}
		free_pipeline(pipeline);
		i++;
	}
	free_double_array(command_line);
	return (exit_status);
}

char	***create_pipeline(char *line, char *envp[])
{
	int		i;
	char	**pipe_split;
	char	***pipeline;

	i = 0;
	pipe_split = ft_split(line, '|');
	pipeline = ft_calloc(sizeof(char**), \
get_length_double_array(pipe_split) + 1);
	while (pipe_split[i])
	{
		pipeline[i] = expand_env_variable(ft_split(pipe_split[i], ' '), envp); //leak
		i++;
	}
	free_double_array(pipe_split);
	return (pipeline);
}

int	verify_pipeline(char ***pipeline, char *command_line, char *envp[])
{
	int	pipes_number;
	int	pipeline_length;

	pipes_number = get_pipes_number(command_line);
	pipeline_length = get_length_pipeline(pipeline);
	if (pipes_number != pipeline_length - 1)
	{
		ft_putendl_fd("Pipeline not correct", STDERR);
		return (0);
	}
	if (verify_executable(pipeline, envp) == 0)
	{
		ft_putendl_fd("Executable does not exists", STDERR);
		return (0);
	}
	return (1);
}

int	verify_executable(char ***pipeline, char *envp[])
{
	int		i;
	char	**path;
	char	*real_exec;

	i = 0;
	path = get_env_path(envp);
	while (pipeline[i])
	{
		if (pipeline[i][0] == NULL)
		{
			free_double_array(path);
			return (0);
		}
		if (!is_absolute_or_relative_path(pipeline[i][0]) && !is_builtin(pipeline[i]))
		{
			real_exec = NULL;
			real_exec = search_executable_in_path(pipeline[i][0], path);
			if (!real_exec)
			{
				free_double_array(path);
				return (0);
			}
			free(real_exec);
		}
		i++;
	}
	free_double_array(path);
	return (1);
}

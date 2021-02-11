/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 10:06:00 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/11 16:48:05 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tokenization(char *line, char **envp[])
{
	int		i;
	int		exit_status;
	char	**command_split;
	char	***pipeline;

	i = 0;
	exit_status = 0;
	command_split = ft_split(line, ';');
	while (command_split[i] && (exit_status != -1 && exit_status != 255))
	{
		//verif tokens
		pipeline = create_pipeline(command_split[i]);
		exit_status = exec_pipeline(pipeline, envp);
		//exit_status = tokenize_pipeline(command_split[i], envp);
		i++;
	}
	i = 0;
	while (pipeline[i])
	{
		free_double_array(pipeline[i]);
		i++;
	}
	free(pipeline);
	free_double_array(command_split);
	return (exit_status);
}

char ***create_pipeline(char *line)
{
	int		i;
	char	**pipe_split;
	char	***pipeline;

	i = 0;
	pipe_split = ft_split(line, '|');
	for (int j = 0; pipe_split[j]; j++)
		printf("pipe_split: %s\n", pipe_split[j]);
	pipeline = ft_calloc(sizeof(char**), get_length_double_array(pipe_split) + 1);
	while(pipe_split[i])
	{
		printf("Command [%d]\n", i);
		pipeline[i] = ft_split(pipe_split[i], ' ');
		for (int k = 0; pipeline[i][k]; k++)
			printf("token: {%s}\n", pipeline[i][k]);
		i++;
	}
	free_double_array(pipe_split);
	return (pipeline);
}
/*
int	tokenize_pipeline(char *command_line, char **envp[])
{
	//int		i;
	int		exit_status;
	char	**pipeline;
	//char	**token;

	//i = 0;
	pipeline = ft_split(command_line, '|');
	exit_status = iterative_pipeline(pipeline, envp);
	//printf("out\n");
	while (pipeline[i] && exit_status != 0)
	{
		token = ft_split(pipeline[i], ' ');
		exit_status = call_builtin(token, envp);
		free_double_array(token);
		i++;
	}
	//printf("token pipe: %d\n", exit_status);
	free_double_array(pipeline);
	return (exit_status);
}
*/
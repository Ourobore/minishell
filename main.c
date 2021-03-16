/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:47:55 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/16 18:50:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_value;

int	main(int argc, char **argv, char *envp[])
{
	int		prompt_loop;
	char	*line;
	char	**envp_copy;

	argc = argc;
	argv = argv;
	prompt_loop = 0;
	exit_value = 0;
	envp_copy = copy_envp(envp);
	/*
	char *term = get_token_value_in_envp("TERM", envp_copy);
	printf("TERM: %s\n", term);
	tgetent(NULL, term);
	if (!envp_copy)
		return (1);

	while (1)
	{
		char *prout;
		
		get_next_line(0, &prout);
		for (int k = 0; k < (int)ft_strlen(prout); k++)
		{
			printf("IN QUOTE: [%d]\t{%c}\n", in_quotes(prout, k), prout[k]);
			if (prout[k] == '\'' || prout[k] == '\"')
				printf("QUOTE CLOSED: [%d]\t{%c}\n", closed_quote(prout, k, prout[k]), prout[k]);
		}
	}
*/
	//struct termios backup;
	//tcgetattr(STDIN, &backup);
	while (prompt_loop != -1 && prompt_loop != 255)
	{
		//printf("in prompt_loop\n");
		//if (line == NULL)
		//{
		//	printf("LINE EQUAL NULL\n");
		//	return (1);
		//}
		//if (verify_quotes(line) == 1)
		//{
		//	ft_putendl_fd("No multilines", STDERR);
		//	continue;
		//}
		//line = prompt_line();
		//line = get_line(backup);
		ft_putstr_fd("\033[1;33m"PROMPT"\033[0;0m", 1);
		get_next_line(0, &line);
		prompt_loop = execution_loop(line, &envp_copy);
		//char *cl_cap = tgetstr("ZO",NULL);
		//tputs (cl_cap, 10, putchar);
		//free(line);
	}
	free_double_array(envp_copy);
	if (prompt_loop == -1 || prompt_loop == 255)
	{
		//printf("in exit child\n");
		exit(-1);
	}
	//Free function
	//wait(NULL);
	printf("exit succes\n");
	exit(EXIT_SUCCESS);
}

int	execution_loop(char *line, char **envp[])
{
	t_lst	*tmp;
	t_lst	*cmd_line;
	int		length_line;
	int		exit_status;

	exit_status = 0;
	length_line = ft_strlen(line);
	cmd_line = NULL;
	cmd_line = add_command_line(cmd_line);
	exit_status = parsing_hub(line, &cmd_line, *envp);
	free(line);
	if (exit_status < 0)
		printf("error parsing\n");
	else if (length_line > 0)
		exit_status = call_builtin_or_pipe(cmd_line, envp);
	while (cmd_line != NULL)
	{
		tmp = cmd_line;
		free_command_list(cmd_line->cmd);
		cmd_line = cmd_line->next;
		free(tmp);
	}
	//close redirs
	//add function for full head free
	//free_command_list(*head);
	//free(head);
	return (exit_status);
}

char	**copy_envp(char *envp[])
{
	int		i;
	int		length;
	char	**copy;

	length = get_length_double_array(envp);
	copy = NULL;
	copy = ft_calloc(sizeof(char*), length + 1);
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

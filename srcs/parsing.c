/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:56:00 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/25 16:21:42 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_line(char *line, char **envp[])
{
	int		i;
	int		j;
	char	*buffer;
	int		exit_status;
	t_cmd	*head;
	t_cmd	*tmp;

	i = 0;
	j = 0;
	exit_status = 0;
	buffer = ft_calloc(sizeof(char), ft_strlen(line) + 1);
	head = ft_calloc(sizeof(*head), 1);
	//add_cmd(&head);
	allocate_list(&head);
	tmp = head;
	//printf("LINE LENGTH: [%ld]\n", ft_strlen(line));
	while (line[i] && i < (int)ft_strlen(line) && exit_status != -1 && exit_status != 255)
	{
		//printf("VERIF LINE[I]: [%c]\n", line[i]);
		//printf("VERIF BUFFER [%d]: [%s]\n", i, buffer);
		if (is_special_character(line[i]) && line[i - 1] != '\\' && !is_in_quotes(line, i))
		{
			if (ft_strlen(buffer) != 0)
			{
				tmp->token = copy_buffer_on_token(tmp, buffer);
				ft_bzero(buffer, ft_strlen(buffer));
				j = 0;
			}
			if (line[i] == ';')
			{
				exit_status = call_builtin_or_pipe(head, buffer, envp); // faire remonter la valeur de retour
				free_command_list(head);
				head = ft_calloc(sizeof(*head), 1);
				tmp = head;
			}
			else if (line[i] == '|')
			{
				if (!add_cmd(&tmp))
				{
					ft_putendl_fd("List memory allocation failed", STDERR);
					break ;
				}
				tmp = tmp->next;
			}
			else if (line[i] == '>') // to upgrade
				tmp->redir_out = get_redirection(tmp, line, &i, buffer);
			else if (line[i] == '<')
				tmp->redir_in = get_redirection(tmp, line, &i, buffer);
		}
		else if (line[i] && line[i] == '\\' && is_in_quotes(line, i) != 1)
		{
			i++;
			continue ;
		}
		//else if (is_in_quotes(line, i) == 2 && line[i] == '$')// et line[i] et env variable
		//{
		//	get_variable();
		//	is_env_variable();
		//	expand_env_variable();
		//}
		else if (line[i] && (is_in_quotes(line, i) || (line[i] != '\'' && line[i] != '\"')))
			buffer[j++] = line[i];
		//else if (line[i] != '\'' && line[i] != '\"')
		//	buffer[j++] = line[i];
		i++;
	}
	//printf("VERIF OUT BUFFER [%d]: [%s]\n", i, buffer);
	if (ft_strlen(buffer) != 0)
	{
		tmp->token = copy_buffer_on_token(tmp, buffer);
		ft_bzero(buffer, ft_strlen(buffer));
	}
	exit_status = call_builtin_or_pipe(head, buffer, envp);
	free(line);
	free_command_list(head);
	free(buffer);
	//while (head != NULL)
	//{
	//	for(int k = 0; (head->token)[k]; k++)
	//		printf("%s\n", (head->token)[k]);
	//	printf("after for\n");
	//	head = head->next;
	//}
	//exec_command
	return (exit_status);
}

char	**copy_buffer_on_token(t_cmd *head, char *buffer)
{
	int		i;
	char	**copy_token;

	i = 0;
	while (head->next != NULL)
		head = head->next;
	copy_token = ft_calloc(sizeof(char*), get_length_double_array(head->token) + 2);
	while (head->token && (head->token)[i])
	{
		copy_token[i] = ft_strdup((head->token)[i]);
		i++;
	}
	copy_token[i] = ft_strdup(buffer);
	if (head->token)
		free_double_array((head->token));
	return (copy_token);
}

int	is_special_character(char c)
{
	if (c == ';' || c == '|' || c == ' ' || c == '>' || c == '<')
		return (1);
	else
		return (0);
}

int	is_in_quotes(char *line, int pos)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (line[i])
	{
		if (i == pos && (i != 0 && line[i - 1] != '\\') && ((line[i] == '\'' && in_single) || (line[i] == '\"' && in_double)))
			return (0);
		if (i < pos)
		{
			if (line[i] == '\'' && (i != 0 && line[i - 1] != '\\'))
				in_single = !in_single;
			else if (line[i] == '\"' && (i != 0 && line[i - 1] != '\\'))
				in_double = !in_double;
		}
		if (i > pos)
		{
			if (line[i] == '\'' && (i != 0 && line[i - 1] != '\\') && in_single)
				return (1);
			else if (line[i] == '\"' && (i != 0 && line[i - 1] != '\\') && in_double)
				return (2);
		}
		i++;
	}
	return (0);
}

int	is_in_line(char *line, char *search)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strncmp(&(line[i]), search, ft_strlen(search)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	verify_quotes(char *line)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double)
			in_single = !in_single;
		if (line[i] == '\"' && !in_single)
			in_double = !in_double;
		i++;
	}
	if (in_single || in_double)
		return (1);
	else
		return (0);
}

//verif redirections

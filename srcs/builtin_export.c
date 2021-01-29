/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 09:19:18 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/29 18:22:09 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_export(char **token, char **envp[])
{
	int		i;
	int		token_index;
	char	**sorted_env;

	i = 1;
	if (!token[1])
	{
		sorted_env = alphabetically_sort_env((*envp));
		print_export(sorted_env);
		free_double_array(sorted_env);
	}
	else
	{
		while (token[i])
		{
			token_index = search_token_in_envp(token[i], *envp);
			printf("token_index: %d\n", token_index);
			if (token_index != -1)
				modify_token_in_envp(token[i], token_index, envp);
			else
				add_token_in_envp(token[i], envp);
			i++;
		}
	}
	return (1);
}

int	add_token_in_envp(char *token, char **envp[])
{
	int		i;
	char	**new_envp;

	i = 0;
	new_envp = NULL;
	new_envp = ft_calloc(sizeof(char*), get_length_double_array((*envp)) + 2);
	if (!new_envp)
		return (-1);
	while ((*envp)[i])
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		i++;
	}
	new_envp[i] = ft_calloc(sizeof(char), ft_strlen(token) + 1);
	if (!new_envp[i])
	{
		free_double_array(new_envp);
		//return error;
	}
	new_envp[i] = ft_strdup(token);
	//free_double_array((*envp));
	(*envp) = new_envp;
	return (0);
}

int	modify_token_in_envp(char *token, int token_index, char **envp[])
{
	char	*new_token;

	new_token = NULL;
	new_token = ft_calloc(sizeof(char), ft_strlen(token) + 1);
	if (!new_token)
		return (-1);
	new_token = ft_strdup(token);
	free((*envp)[token_index]);
	(*envp)[token_index] = new_token;
	return (0);
}

int	print_export(char **sorted_env)
{
	int	i;
	int	j;
	int	first_equal;

	i = 0;
	while (sorted_env[i])
	{
		j = 0;
		first_equal = 1;
		ft_putstr_fd("declare -x ", 1);
		while (sorted_env[i][j])
		{
			ft_putchar_fd(sorted_env[i][j], 1);
			if (sorted_env[i][j++] == '=' && first_equal)
			{
				ft_putchar_fd('"', 1);
				first_equal = 0;
			}
		}
		if (!first_equal)
			ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (1);
}

char	**alphabetically_sort_env(char *envp[])
{
	int		i;
	char	**sorted_env;

	sorted_env = NULL;
	sorted_env = ft_calloc(sizeof(char*), get_length_double_array(envp) + 1);
	if (!sorted_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		sorted_env[i] = ft_strdup(envp[i]);
		i++;
	}
	sorted_env = alphabetical_bubble_sort(sorted_env);
	return (sorted_env);
}

char	**alphabetical_bubble_sort(char **array)
{
	int		i;
	int		sort_done;
	char	*tmp;

	sort_done = 0;
	while (!sort_done)
	{
		i = 0;
		sort_done = 1;
		while (array[i] && array[i + 1] != NULL)
		{
			if (ft_strcmp(array[i], array[i + 1]) > 0)
			{
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
				sort_done = 0;
			}
			i++;
		}
	}
	return (array);
}

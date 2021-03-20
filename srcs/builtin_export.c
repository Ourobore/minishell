/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 09:19:18 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/20 09:10:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_export(char **token, char **envp[])
{
	int		exit_status;
	char	**sorted_env;

	exit_status = 0;
	if (!token[1])
	{
		for(int i = 0; (*envp)[i]; i++)
			printf("prout[i]: %s\n", (*envp)[i]);
		sorted_env = alphabetically_sort_env((*envp));
		print_export(sorted_env);
		free_double_array(sorted_env);
	}
	else
		exit_status = export_token(token, envp);
	return (exit_status);
}

int	export_token(char **token, char **envp[])
{
	int	i;
	int	token_index;
	int	exit_status;

	i = 1;
	exit_status = 0;
	while (token[i])
	{
		if (!valid_token(token[i]))
		{
			print_not_valid_idendifier(token[i]);
			exit_status = 1;
		}
		else
		{
			token_index = search_token_in_envp(token[i], *envp);
			if (token_index != -1)
				modify_token_in_envp(token[i], token_index, envp);
			else
				add_token_in_envp(token[i], envp);
		}
		i++;
	}
	return (exit_status);
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
	sorted_env = ft_calloc(sizeof(char *), get_length_double_array(envp) + 1);
	if (!sorted_env)
		return (NULL);
	i = 0;
	printf("before\n");
	while (envp[i])
	{
		printf("envp[i]: %s\n", envp[i]);
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

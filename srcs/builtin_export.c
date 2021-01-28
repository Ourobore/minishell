/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 09:19:18 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/28 11:32:45 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_export(char **token, char *envp[])
{
	int 	i;
	char	**sorted_env;

	i = 0;
	if (!token[1])
	{
		sorted_env = alphabetically_sort_env(envp);
		while (sorted_env[i])
		{
			ft_putstr_fd(sorted_env[i], 1);
			ft_putchar_fd('\n', 1);
			i++;
		}
		free_double_array(sorted_env);
	}
	else if (!token[2])
		printf("Not done yet 1\n");
	else
		printf("Not done yet 2\n");
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

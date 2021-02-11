/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 20:09:34 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/01 14:52:01 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	//new_envp[i] = ft_calloc(sizeof(char), ft_strlen(token) + 1);
	new_envp[i] = ft_strdup(token);
	if (!new_envp[i])
	{
		free_double_array(new_envp);
		//return error;
	}
	//new_envp[i] = ft_strdup(token);
	free_double_array((*envp));
	(*envp) = new_envp;
	return (0);
}

int	modify_token_in_envp(char *token, int token_index, char **envp[])
{
	char	*new_token;

	//new_token = NULL;
	//new_token = ft_calloc(sizeof(char), ft_strlen(token) + 1);
	//if (!new_token)
	//	return (-1);
	new_token = ft_strdup(token);
	//printf("before verif: %s\n", (*envp)[token_index]);
	free((*envp)[token_index]);
	(*envp)[token_index] = new_token;
	//printf("after verif: %s\n", (*envp)[token_index]);
	return (0);
}

int	search_token_in_envp(char *token, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(token, envp[i], characters_before_equal(token)) == 0 && (\
envp[i][characters_before_equal(token)] == '=' || \
envp[i][characters_before_equal(token)] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int	remove_token_in_envp(int token_index, char **envp[])
{
	int		i;
	int		j;
	int		exit_status;
	char	**new_envp;

	exit_status = 1;
	new_envp = NULL;
	new_envp = ft_calloc(sizeof(char*), get_length_double_array(*envp));
	if (!new_envp)
		return (exit_status);
	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		if (i != token_index)
			new_envp[j++] = ft_strdup((*envp)[i++]);
		else
		{
			exit_status = 0;
			i++;
		}
	}
	free_double_array(*envp);
	*envp = new_envp;
	return (exit_status);
}

char	*get_token_value_in_envp(char *token, char *envp[])
{
	int		i;
	int		j;
	char	*value;

	j = 0;
	i = search_token_in_envp(token, envp);
	if (i == -1)
		return (NULL);
	//printf("before: %s\n", envp[i]);
	while (envp[i] && envp[i][j] != '=')
		j++;
	j++;
	//printf("after: %s\n", envp[i]);
	value = ft_strdup(envp[i] + j);
	return (value);
}

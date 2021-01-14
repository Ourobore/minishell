/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:47:55 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/14 10:40:29 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	int		loop;
	char	*line;
	char	**split;

	loop = 1;
	printf("%d\n", ft_strcmp("a", "A"));
	while (loop > 0)
	{
		loop = prompt_line(&line);
		split = ft_split(line, ' ');
		for(int i = 0; split[i]; i++)
		{
			ft_putstr_fd(split[i], 1);
			ft_putchar_fd('\n', 1);
		}
		for(int i = 0; split[i]; i++)
			free(split[i]);
		free(split);
		free(line);
	}
	//fonction de free

}
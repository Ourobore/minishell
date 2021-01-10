/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:47:55 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/10 11:56:09 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	int fd;
	int ret = 1;
	char *line;

	fd = open("main.c", O_RDONLY);
	while(ret == 1)
	{
		ret = get_next_line(fd, &line);
		printf("LINE:%s\n", line);
		free(line);
	}
	//
	ret = get_next_line(fd, &line);
	printf("LINE:%s\n", line);
	free(line);
	close (fd);
}
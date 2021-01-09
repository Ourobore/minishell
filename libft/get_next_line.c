/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:59:24 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/09 17:00:35 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_cat(char *s, char c)
{
	int		i;
	char	*cat;

	i = 0;
	while (s[i] != 0)
		i++;
	cat = malloc(sizeof(*cat) * (i + 2));
	if (!cat)
		return (NULL);
	i = 0;
	while (s[i] != 0)
	{
		cat[i] = s[i];
		i++;
	}
	cat[i] = c;
	cat[i + 1] = 0;
	free(s);
	return (cat);
}

int	get_next_line(int fd, char **line)
{
	char	*cat;
	char	buf;
	int		ret;

	cat = malloc(sizeof(char) * 1);
	if (fd < 0 || !line || !cat)
		return (-1);
	cat[0] = 0;
	ret = 1;
	while (ret != 0)
	{
		ret = read(fd, &buf, 1);
		if (ret == -1)
			return (-1);
		if (buf == '\n')
			break ;
		cat = ft_cat(cat, buf);
	}
	*line = cat;
	if (*line == NULL)
		ret = -1;
	return (ret);
}

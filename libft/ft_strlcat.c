/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:19:56 by lchapren          #+#    #+#             */
/*   Updated: 2019/11/07 17:54:29 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	longueur;

	i = 0;
	j = 0;
	longueur = ft_strlen(dst) + ft_strlen(src);
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize < ft_strlen(dst))
		return (ft_strlen(src) + dstsize);
	while (dst[i] && i < dstsize)
		i++;
	while (src[j] && i < dstsize - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = 0;
	return (longueur);
}

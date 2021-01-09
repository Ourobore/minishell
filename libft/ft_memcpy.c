/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:13:18 by lchapren          #+#    #+#             */
/*   Updated: 2019/11/07 17:45:29 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long int	i;
	unsigned char		*tmp;
	unsigned char		*tsrc;

	i = 0;
	tmp = (unsigned char*)dst;
	tsrc = (unsigned char*)src;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		tmp[i] = tsrc[i];
		i++;
	}
	return (dst);
}

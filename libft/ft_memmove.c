/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:24:26 by lchapren          #+#    #+#             */
/*   Updated: 2019/11/07 17:48:52 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned long int	i;
	unsigned char		*d;
	unsigned char		*s;

	i = 0;
	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	if (!dst && !src)
		return (NULL);
	if (src < dst)
		while (i++ < len)
			d[len - i] = s[len - i];
	else
		while (i++ < len)
			*(d++) = *(s++);
	return (dst);
}

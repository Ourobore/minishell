/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:13:18 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/16 21:07:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long int	i;
	unsigned char		*tmp;
	unsigned char		*tsrc;

	i = 0;
	tmp = (unsigned char *)dst;
	tsrc = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		tmp[i] = tsrc[i];
		i++;
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:37:17 by lchapren          #+#    #+#             */
/*   Updated: 2019/11/09 13:47:07 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned long int	i;
	unsigned char		*dtmp;
	unsigned char		*stmp;

	i = 0;
	dtmp = (unsigned char*)dst;
	stmp = (unsigned char*)src;
	while (i < n)
	{
		if (i > 0 && stmp[i - 1] == (unsigned char)c)
			return (dst + i);
		dtmp[i] = stmp[i];
		i++;
	}
	if (stmp[n - 1] == c)
		return (dst + i);
	return (NULL);
}

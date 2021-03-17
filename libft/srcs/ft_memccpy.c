/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:37:17 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/16 21:11:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned long int	i;
	unsigned char		*dtmp;
	unsigned char		*stmp;

	i = 0;
	dtmp = (unsigned char *)dst;
	stmp = (unsigned char *)src;
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

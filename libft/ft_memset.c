/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 09:34:16 by lchapren          #+#    #+#             */
/*   Updated: 2019/11/07 17:51:40 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned long int	i;
	unsigned char		*tmp;

	i = 0;
	tmp = (unsigned char*)b;
	while (i < len)
	{
		tmp[i] = c;
		i++;
	}
	return (b);
}

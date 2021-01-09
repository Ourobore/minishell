/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:17:57 by lchapren          #+#    #+#             */
/*   Updated: 2019/11/07 17:42:01 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*alloc;

	alloc = NULL;
	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	alloc = malloc(count * size);
	if (!alloc)
		return (alloc);
	ft_bzero(alloc, count * size);
	return (alloc);
}

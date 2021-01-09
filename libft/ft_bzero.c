/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:43:57 by lchapren          #+#    #+#             */
/*   Updated: 2019/11/07 17:41:43 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned long int	i;
	unsigned char		*tmp;

	i = 0;
	tmp = (unsigned char *)s;
	while (i < n)
	{
		tmp[i] = 0;
		i++;
	}
}

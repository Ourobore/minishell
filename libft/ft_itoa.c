/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 08:33:18 by lchapren          #+#    #+#             */
/*   Updated: 2019/11/08 10:51:03 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_char(int n)
{
	long int			nbl;
	unsigned long int	count;

	nbl = n;
	count = 0;
	if (nbl == 0)
		count = 1;
	if (nbl < 0)
	{
		count++;
		nbl *= -1;
	}
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*s;
	long int	nb;
	int			i;
	int			len;

	i = 0;
	len = nb_char(n);
	nb = n;
	s = malloc((sizeof(char) * len) + 1);
	if (!s)
		return (s);
	if (nb == 0)
		s[0] = '0';
	if (nb < 0)
	{
		s[0] = 45;
		nb = -nb;
	}
	while (nb)
	{
		s[(len - 1) - i++] = (nb % 10) + 48;
		nb /= 10;
	}
	s[len] = 0;
	return (s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 10:24:42 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/16 21:49:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	c1;
	unsigned char	c2;

	c1 = (const unsigned char)*s1;
	c2 = (const unsigned char)*s2;
	while (c1 == c2 && c1 != '\0')
	{
		c1 = (const unsigned char)*s1++;
		c2 = (const unsigned char)*s2++;
	}
	return (c1 - c2);
}

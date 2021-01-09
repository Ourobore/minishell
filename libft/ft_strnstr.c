/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 09:28:15 by lchapren          #+#    #+#             */
/*   Updated: 2019/11/07 17:55:51 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned long int	i;
	unsigned long int	j;

	i = 0;
	j = 0;
	if (needle[i] == 0)
		return ((char *)haystack);
	while (haystack[i] && needle[j])
	{
		while (haystack[i] == needle[j] && i < len)
		{
			if (needle[j + 1] == 0)
				return ((char *)&haystack[i - j]);
			i++;
			j++;
		}
		i = (i - j) + 1;
		j = 0;
	}
	return (NULL);
}

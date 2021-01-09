/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:32:23 by lchapren          #+#    #+#             */
/*   Updated: 2019/11/11 15:54:33 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned long int	i;
	unsigned long int	j;
	char				*cp;

	i = 0;
	j = start;
	if (!s || len == 0 || start > ft_strlen(s))
	{
		cp = ft_calloc(1, 1);
		if (!cp)
			return (NULL);
		return (cp);
	}
	cp = ft_calloc(len + 1, sizeof(char));
	if (!cp)
		return (NULL);
	while (i < len && s[i])
	{
		cp[i] = s[j];
		i++;
		j++;
	}
	return (cp);
}

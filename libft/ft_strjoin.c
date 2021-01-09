/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:03:49 by lchapren          #+#    #+#             */
/*   Updated: 2019/11/07 17:54:07 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned long int	i;
	unsigned long int	j;
	unsigned long int	l;
	char				*cat;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	l = ft_strlen(s1) + ft_strlen(s2);
	cat = malloc((l * sizeof(char)) + 1);
	if (!cat)
		return (NULL);
	while (s1[j])
		cat[i++] = s1[j++];
	j = 0;
	while (s2[j])
		cat[i++] = s2[j++];
	cat[i] = 0;
	return (cat);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:17:37 by lchapren          #+#    #+#             */
/*   Updated: 2019/11/11 12:02:47 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char c, char const *set)
{
	unsigned long int	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

static char	*set_zero(char *trim)
{
	trim = malloc(1 * sizeof(char));
	if (!trim)
		return (NULL);
	trim[0] = 0;
	return (trim);
}

static int	get_len(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (in_set(s1[i], set))
	{
		len++;
		i++;
	}
	if (len == ft_strlen(s1))
		return (ft_strlen(s1));
	i = ft_strlen(s1) - 1;
	while (in_set(s1[i], set))
	{
		len++;
		i--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	taille;
	char	*trim;

	i = 0;
	j = 0;
	trim = NULL;
	if (!s1)
		return (NULL);
	len = get_len(s1, set);
	taille = ft_strlen(s1) - len;
	if (len == ft_strlen(s1) || s1[0] == 0)
		return (set_zero(trim));
	trim = malloc((taille + 1) * sizeof(char));
	if (!trim)
		return (NULL);
	while (in_set(s1[j], set))
		j++;
	while (taille--)
		trim[i++] = s1[j++];
	trim[i] = 0;
	return (trim);
}

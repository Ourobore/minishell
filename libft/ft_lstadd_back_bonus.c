/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 09:46:58 by lchapren          #+#    #+#             */
/*   Updated: 2019/11/13 09:47:01 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (!alst)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	while ((*alst)->next)
		*alst = (*alst)->next;
	(*alst)->next = new;
}

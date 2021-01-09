/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:30:29 by lchapren          #+#    #+#             */
/*   Updated: 2019/11/07 17:52:23 by lchapren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nbl;

	nbl = n;
	if (nbl < 0)
	{
		write(fd, "-", 1);
		nbl = nbl * -1;
	}
	if (nbl >= 0 && nbl <= 9)
		ft_putchar_fd(nbl + 48, fd);
	else
	{
		ft_putnbr_fd(nbl / 10, fd);
		ft_putchar_fd((nbl % 10) + 48, fd);
	}
}

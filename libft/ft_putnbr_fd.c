/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:28:33 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/12 11:52:57 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			n *= -1;
			write(fd, "-", 1);
		}
		if (n >= 10)
			ft_putnbr_fd((n - n % 10) / 10, fd);
		c = n % 10 + '0';
		write(fd, &c, 1);
	}
}
/*
int main(void)
{
	ft_putnbr_fd(10, 1);
}
*/
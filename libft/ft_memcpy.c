/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:18:49 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/18 09:54:35 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*c_src;
	unsigned char	*c_dest;

	c_src = (unsigned char *)src;
	c_dest = (unsigned char *)dest;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		c_dest[i] = c_src[i];
		i += 1;
	}
	return (dest);
}
/*
int main () {
   const char src[50] = "123456789/ww.com";
   char dest[50] = "Heloooo!!";
   pritf("Before memcp dest = %d\n", 0);
   ft_memcpy(((void *)0), ((void *)0), 0);
   prinf("After memcp dest = %d\n", 0);
}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:10:33 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/18 09:54:27 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr( const void *mem, int chr, size_t size )
{
	size_t	i;
	char	*tmem;
	char	c_chr;

	i = 0;
	tmem = (char *)mem;
	c_chr = (char)chr;
	while (i < size)
	{
		if (*(tmem + i) == c_chr)
			return (tmem + i);
		i += 1;
	}
	return (NULL);
}
/*
int main(void)
{
	char *src = "/|\x12\xff\x09\x42\2002\42|\\";
	prntf("%s\n", ft_memchr(src, '\200', '\200'));
	prinf("%s", memch(src, '\200', '\200'));
}*/
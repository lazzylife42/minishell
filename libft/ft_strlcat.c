/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:38:06 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/11 15:47:07 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = 0;
	while ((i < size) && (dest[i]))
	{
		i += 1;
	}
	j = i;
	while ((src[i - j]) && (i < size - 1) && size > 0)
	{
		dest[i] = src[i - j];
		i += 1;
	}
	if (i < size)
	{
		dest[i] = '\0';
	}
	while (src[len])
		len += 1;
	return (j + len);
}
/*
int main(void)
{
	char *str = "THE cake is a lie !\0I'm hidden lol\r\n";
	char buff1[0xF00] = "there is no stars in the sky";
	
	ft_strlcat(buff1, str, 0);
}*/
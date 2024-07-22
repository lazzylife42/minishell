/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:02:59 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/18 09:54:11 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp( const void *str1, const void *str2, size_t size)
{
	size_t			i;
	unsigned char	*c_str1;
	unsigned char	*c_str2;

	c_str1 = (unsigned char *) str1;
	c_str2 = (unsigned char *) str2;
	i = 0;
	while (i < size)
	{
		if (c_str1[i] != c_str2[i])
			return (c_str1[i] - c_str2[i]);
		i += 1;
	}
	return (0);
}
/*
int main(void)
{
	pintf("%d", ft_memcmp("baba", "baba", 1000));    
}*/
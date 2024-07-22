/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:18:44 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/18 09:54:24 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*c_s;

	c_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		c_s[i] = '\0';
		i += 1;
	}
}
/*
int main () {
   char str[50] = "Je fgfj";
   pritf("%s\n", str);

   ft_bzero(str, 3);
   pintf("%s", str);
   
   return(0);
}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:18:55 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/18 09:54:08 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*strf;
	size_t			i;

	strf = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		strf[i] = (unsigned char)c;
		i += 1;
	}
	return (str);
}
/*
int main () {
   char str[] = "Je ";
   pritf("%s\n", str);

   ft_memset(str,'d',7);
   prinf("%s", str);
   
   return(0);
}*/
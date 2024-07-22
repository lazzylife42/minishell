/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:09 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/18 09:52:00 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove( void *dest, const void *src, size_t n )
{
	char	*c_src;
	char	*c_dest;
	size_t	i;

	if (!n)
		return (dest);
	c_src = (char *)src;
	c_dest = (char *)dest;
	i = 0;
	if (!dest && !src)
		return (NULL);
	if (c_dest > c_src)
		while (n-- > 0)
			c_dest[n] = c_src[n];
	else
	{
		while (i < n)
		{
			c_dest[i] = c_src[i];
			i += 1;
		}
	}
	return (dest);
}
/*
int main ()
{
  char str[] = "memove can be very useful......";
  memove (str+15,str+20,11);
  puts (str);
  return 0;
}*/
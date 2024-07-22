/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:38:06 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/18 09:52:52 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	int		n;
	size_t	i;

	n = 0;
	i = 0;
	if (size == 0)
	{
		while (src[n])
			n += 1;
		return (n);
	}
	while ((i < (size - 1)) && src[i])
	{
		dest[i] = src[i];
		i += 1;
	}
	if (size > 0)
		dest[i] = '\0';
	while (src[n])
		n += 1;
	return (n);
}
/*
int main(void)
{
	char dest1[] = "aaaaaaa";
	char dest2[] = "aaaaaaa";
	char str[] = "bb";
	size_t a = 0;
	pritf("%zu\n",strlcy(dest1, str, a));
	prntf("%zu",ft_strlcy(dest2, str, a));

}*/
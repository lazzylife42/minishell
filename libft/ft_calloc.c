/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:57:12 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/17 15:43:47 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc( size_t count, size_t size )
{
	void	*res;
	size_t	i;

	i = 0;
	res = malloc(count * size);
	if (res == NULL)
		return (NULL);
	while (i < count * size)
	{
		((char *)res)[i] = 0;
		i += 1;
	}
	return (res);
}
/*
int main(void)
{
	char *str = (char *) ft_calloc(5,4);
	*str = 'a';
}*/
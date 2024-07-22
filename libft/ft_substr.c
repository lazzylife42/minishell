/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:40:11 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/18 09:53:37 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	size;
	size_t	t_len;
	char	*res;
	size_t	i;

	size = 0;
	t_len = 0;
	i = 0;
	while (str[size])
		size += 1;
	if (start > size)
		len = 0;
	else
		while (str[start + t_len] && t_len < len)
			t_len += 1;
	res = malloc(t_len + 1);
	if (res == NULL)
		return (NULL);
	while (i < t_len)
	{
		res[i] = str[start + i];
		i += 1;
	}
	res[i] = '\0';
	return (res);
}
/*
int main(void)
{

	pritf("%s\n",ft_substr("", 1, 1));
}*/
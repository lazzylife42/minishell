/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:59:42 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/18 09:52:42 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_l(char const *s1, char const *s2)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	while (s1[a])
		a += 1;
	while (s2[b])
		b += 1;
	return (a + b);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*res;

	len = 0;
	i = 0;
	j = 0;
	len = get_l(s1, s2);
	res = malloc(len + 1);
	if (res == NULL)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i += 1;
	}
	while (s2[j])
	{
		res[i + j] = s2[j];
		j += 1;
	}
	res[i + j] = '\0';
	return (res);
}
/*
int main(void)
{
	rintf("%s", ft_strjoin("lalala", "bbobobo"));
}*/
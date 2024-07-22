/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:22:45 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/18 09:53:28 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isinset(char chr, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (chr == set[i])
			return (1);
		i += 1;
	}
	return (0);
}

static int	get_len(char const *str, char const *set)
{
	size_t	len;
	size_t	i;
	size_t	len_po;

	len = 0;
	len_po = 0;
	i = 0;
	while (isinset(str[i], set))
		i += 1;
	while (str[i])
	{
		if (isinset(str[i], set))
			len_po += 1;
		else
		{
			len += 1 + len_po;
			len_po = 0;
		}
		i += 1;
	}
	return (len);
}

char	*ft_strtrim(char const *str, char const *set)
{
	size_t	len;
	size_t	j;
	size_t	start;
	char	*res;

	start = 0;
	j = 0;
	len = get_len(str, set);
	res = malloc(len + 1);
	if (res == NULL)
		return (NULL);
	while (isinset(str[start], set))
		start += 1;
	while (j < len)
	{
		res[j] = str[start + j];
		j += 1;
	}
	res[j] = '\0';
	return (res);
}
/*
int main (void)
{
	pritf("%s", ft_strtrim("2797545", "0123456789"));

}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:46:28 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/18 09:53:17 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*c_big;
	char	*c_little;

	i = 0;
	j = 0;
	c_big = (char *) big;
	c_little = (char *) little;
	if (*c_little == 0)
		return (c_big);
	while (c_big[i])
	{
		while (c_little[j] == c_big[i + j] && (i + j < len))
		{
			j += 1;
			if (!c_little[j])
				return (c_big + i);
		}
		j = 0;
		i += 1;
	}
	return (NULL);
}
/*
int main(void)
{
	char *big = "abcdef";
	char *little = "abc";
	size_t max = 6;

	pintf("%s\n", ststr(big, little, max));
	prntf("%s", ft_strnstr(big, little, max));

}*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:30:30 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/18 09:53:02 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
char test(unsigned int n, char chr)/////
{
	char res = n + chr;
	return (res);
}

static size_t	get_len(const char *str)
{
	size_t	n;

	n = 0;
	while (str[n])
		n += 1;
	return (n);
}

char	*ft_strdup( const char *src )/////
{
	int		len;
	int		i;
	char	*res;

	len = 0;
	i = 0;
	while (src[len])
		len += 1;
	res = malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (src[i])
	{
		res[i] = src[i];
		i += 1;
	}
	res[i] = '\0';
	return (res);
}
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	char			*res;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	res = ft_strdup(s);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = f(i, res[i]);
		i += 1;
	}
	return (res);
}
/*
int	main (void)
{
	prntf("%s", ft_strmapi("babu",*test));
}*/
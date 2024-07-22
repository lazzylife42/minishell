/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:52:51 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/18 09:54:31 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr( const char *str, int chr )
{
	char	*tstr;
	char	c_chr;

	c_chr = (char)chr;
	tstr = (char *)str;
	while (*tstr || c_chr == '\0')
	{
		if (*tstr == c_chr)
			return (tstr);
		tstr += 1;
	}
	return (NULL);
}
/*
int main(void)
{
	//char *src = "there is so \0ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";
	//char *d1 = strhr(src, '4');
	char *d2 = ft_strchr("teste",'e' + 256);
	pritf("%s",d2);
}*/
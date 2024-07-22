/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:52:51 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/18 09:53:22 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr( const char *str, int chr )
{
	char	*tstr;
	char	*mem;
	char	c_chr;

	c_chr = (char)chr;
	tstr = (char *) str;
	mem = tstr;
	while (*tstr)
		tstr += 1;
	while (tstr != mem - 1)
	{
		if (*tstr == c_chr)
			return (tstr);
		tstr -= 1;
	}
	return (NULL);
}
/*
int main(void)
{
	prntf("%s", ft_strrchr("abccdbce", '7'));
}*/
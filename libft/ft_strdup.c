/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:13:03 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/18 09:54:00 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup( const char *src )
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
/*
int main(void)
{
	char a[] = "sakl";
	pintf("%s", ft_strdup(a));

}*/
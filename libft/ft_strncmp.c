/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:02:59 by nreichel          #+#    #+#             */
/*   Updated: 2023/12/20 14:50:10 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp( const char *str1, const char *str2, size_t len)
{
	size_t			i;
	unsigned char	*u_str1;
	unsigned char	*u_str2;

	if (str1 && str2)
	{
		u_str1 = (unsigned char *) str1;
		u_str2 = (unsigned char *) str2;
		i = 0;
		while (i < len)
		{
			if (u_str1[i] == u_str2[i] && u_str1[i] == '\0')
				return (0);
			if (u_str1[i] != u_str2[i])
				return (u_str1[i] - u_str2[i]);
			i += 1;
		}
		return (0);
	}
	return (-1);
}

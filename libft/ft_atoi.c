/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:45:57 by nreichel          #+#    #+#             */
/*   Updated: 2024/01/10 13:03:17 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi( const char *str )
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	if (!str)
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str += 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str += 1;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str += 1;
	}
	return (res * sign);
}
/*
int main(void)
{
	prinf("%d", ft_atoi("      -245jasf"));
}*/
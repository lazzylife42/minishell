/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:58:32 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/18 09:54:42 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	str_invert(char *str)
{
	int	i;
	int	mem;
	int	size;

	size = 0;
	while (str[size])
		size += 1;
	i = 0;
	while (i < size / 2)
	{
		mem = str[i];
		str[i] = str[size - i - 1];
		str[size - i - 1] = mem;
		i += 1;
	}	
}

static char	*fill(int n, char *str, int sign)
{
	int		count;

	count = 0;
	while (n > 0)
	{
		str[count] = n % 10 + '0';
		n /= 10;
		count += 1;
	}
	if (sign == -1)
	{
		str[count] = '-';
		count += 1;
	}
	str[count] = '\0';
	return (str);
}

static int	get_len(int n)
{
	int	res;

	res = 0;
	while (n > 0)
	{
		n /= 10;
		res += 1;
	}
	return (res);
}

static char	*exception(char *nbr)
{
	char	*res;
	int		i;
	int		len;

	len = 0;
	while (nbr[len])
		len += 1;
	i = 0;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	while (nbr[i])
	{
		res[i] = nbr[i];
		i += 1;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*res;

	sign = 1;
	if (n == -2147483648)
		return (exception("-2147483648"));
	if (n == 0)
		return (exception("0"));
	if (n < 0)
	{
		sign *= -1;
		n *= -1;
	}
	res = malloc(get_len(n) + 1 + (sign == -1));
	if (!res)
		return (NULL);
	res = fill(n, res, sign);
	str_invert(res);
	return (res);
}
/*
int main(void)
{
	pritf("%s", ft_itoa(-2147483648));


}*/
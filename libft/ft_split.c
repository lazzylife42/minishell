/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:40:17 by nreichel          #+#    #+#             */
/*   Updated: 2023/12/11 13:31:57 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_entry_nbr(char const *str, char chr)
{
	int	res;
	int	val;

	val = 1;
	res = 0;
	while (*str)
	{
		if (*str != chr)
		{
			if (val)
			{
				res += 1;
				val = 0;
			}
		}
		else
			val = 1;
		str += 1;
	}
	return (res);
}

static char	*return_str(char const *str, int nbr)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(nbr + 1);
	if (!res)
		return (0);
	while (i < nbr)
	{
		res[i] = str[i];
		i += 1;
	}
	res[i] = '\0';
	return (res);
}

static int	clear(char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i += 1;
	}
	free(res);
	return (1);
}

static char	**ft_split2(char const *str, char chr, int count, int i)
{
	char	**res;

	res = malloc((get_entry_nbr(str, chr) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (*str)
	{
		i = 0;
		while (str[i] != chr && str[i] != '\0')
			i += 1;
		if (i > 0)
		{
			res[count] = return_str(str, i);
			if (!res[count])
				if (clear(res))
					return (NULL);
			count += 1;
			str += i;
		}
		else
			str += 1;
	}
	res[count] = 0;
	return (res);
}

char	**ft_split(char const *str, char chr)
{
	return (ft_split2(str, chr, 0, 0));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:26:29 by nreichel          #+#    #+#             */
/*   Updated: 2024/01/23 09:46:10 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*alloc_first(char *str, int len)
/* Function used by translate.c */
{
	int		i;
	char	*res;

	i = 0;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		shell_exit(1, NULL);
	while (i < len)
	{
		res[i] = str[i];
		i += 1;
	}
	res[i] = '\0';
	return (res);
}

char	*alloc_re(char *res, char *str, int len)
{
	char	*new_res;
	int		i;
	int		y;

	i = 0;
	y = 0;
	new_res = malloc((ft_strlen(res) + len + 1) * sizeof(char));
	if (!new_res)
		shell_exit(1, NULL);
	while (i < (int)ft_strlen(res))
	{
		new_res[i] = res[i];
		i += 1;
	}
	while (y < len)
	{
		new_res[i + y] = str[y];
		y += 1;
	}
	new_res[i + y] = '\0';
	return (new_res);
}

char	*ralloc_str(char *res, char *str, int len)
{
	char	*new_res;

	if (!res)
		new_res = alloc_first(str, len);
	else
		new_res = alloc_re(res, str, len);
	if (!new_res)
		shell_exit(1, NULL);
	free(res);
	return (new_res);
}

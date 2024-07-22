/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonte-e <smonte-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:14:35 by nreichel          #+#    #+#             */
/*   Updated: 2024/01/30 10:02:34 by smonte-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*translate_single_quote(char *str)
{
	int		y;
	char	*res;

	res = ft_strdup(str);
	if (!res)
		exit (1);
	if (res[0] == '\'')
	{
		y = 1;
		while (res[y] != '\'')
		{
			res[y - 1] = res[y];
			y += 1;
		}
		res[y - 1] = 0;
	}
	return (res);
}

char	*translate_double_quote(char *str, char **env, int y, char *res)
//variable in declaration to save lines
{
	char	*check;
	int		len;

	while (str[y])
	{
		if (str[y] != '"')
		{
			if (str[y] != '$')
				res = ralloc_str(res, str + y, 1);
			else
			{
				y += 1;
				len = 0;
				while (str[y + len] && str[y + len] != ' '
					&& str[y + len] != '"' && str[y + len] != '\'')
					len += 1;
				check = check_env(env, str + y, len);
				if (check)
					res = ralloc_str(res, check, ft_strlen(check));
				y += len - 1;
			}
		}
		y += 1;
	}
	return (res);
}

char	*translate_quote(char *str, char **env)
{
	char	*res;

	res = NULL;
	if (!str)
		return (NULL);
	if (str[0] != '\'')
		res = translate_double_quote(str, env, 0, NULL);
	else
		res = translate_single_quote(str);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 09:29:55 by nreichel          #+#    #+#             */
/*   Updated: 2024/01/29 11:03:32 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display(char *str, bool sing, bool extra)
{
	int	j;

	j = -1;
	if (extra)
	{
		printf("declare -x ");
		if (!sing)
		{
			while (str[++j])
			{
				printf("%c", str[j]);
				if (str[j] == '=')
					printf("\"");
			}
			printf("\"\n");
		}
		else
			printf("%s\n", str);
	}
	else
		if (!sing)
			printf("%s\n", str);
}

void	display_env(char ***env, bool extra)
{
	int		i;
	bool	sing;

	i = 0;
	sing = false;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], "?=", 2) != 0)
			display((*env)[i], ft_strchr((*env)[i], '=') == NULL, extra);
		i += 1;
	}
	set_dollar(env, 0);
}

void	echo(char **input, char ***env)
{
	int		i;
	int		backslash;
	char	*txt;

	i = 0;
	backslash = true;
	while (input[i])
	{
		txt = translate_quote(input[i], *env);
		if (!txt)
			return ;
		if (ft_strncmp(txt, "-n", 3) == 0 && i == 0)
			backslash = false;
		else
		{
			if ((backslash && i >= 1) || (!backslash && i >= 2))
				printf(" ");
			printf("%s", txt);
		}
		i += 1;
		free(txt);
	}
	if (backslash)
		printf("\n");
	set_dollar(env, 0);
}

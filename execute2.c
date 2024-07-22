/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:24:29 by nreichel          #+#    #+#             */
/*   Updated: 2024/01/26 11:26:20 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**translate_for_exec(char **argv, char ***env)
{
	char	**res;
	int		i;

	i = -1;
	res = malloc(sizeof(char *) * (double_str_len(argv) + 1));
	if (!res)
		return (NULL);
	while (argv[++i])
		res[i] = translate_quote(argv[i], *env);
	res[i] = NULL;
	return (res);
}

void	no_cmd(char *txt, char ***env)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(txt, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	set_dollar(env, 127);
}

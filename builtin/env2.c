/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 09:26:32 by nreichel          #+#    #+#             */
/*   Updated: 2024/01/26 11:31:03 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_valid(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (!(ft_isalpha(*var) || *var == '_'))
		{
			ft_putstr_fd("unset: invalid parameter name\n", STDERR_FILENO);
			return (0);
		}
		i += 1;
	}
	return (1);
}

char	*check_env(char **env, char *str, int len)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			if (ft_strncmp(env[i], str, len) == 0
				&& (env[i][len] == '=' || !env[i][len]))
				return (env[i] + len + 1);
			i += 1;
		}
	}
	return (NULL);
}

void	set_env_us(char ***env, char *txt)
{
	char	*path;
	char	*str;

	path = find_path(txt, *env);
	if (path)
		str = ft_strjoin("_=", path);
	else
		str = ft_strjoin("_=", txt);
	if (!str)
		shell_exit(1, NULL);
	export_one(env, str, true);
	free(path);
	free(str);
}

void	env_ralloc_del(char ***env, int *pos)
{
	char	**res;
	int		i;
	int		off;

	i = 0;
	off = 0;
	res = malloc(double_str_len(*env) * sizeof(char *));
	if (!res)
		return ;
	while ((*env)[i])
	{
		if (i != *pos)
			res[i - off] = (*env)[i];
		else
		{
			free((*env)[i]);
			off = 1;
		}
		i += 1;
	}
	res[i - off] = NULL;
	free(*env);
	*env = res;
	*pos -= 1;
}

bool	env_var_valid(char *var, bool admin)
{
	if (admin)
		return (1);
	if (ft_strncmp(var, "_=", 2) == 0 || ft_strncmp(var, "_", 2) == 0)
		return (false);
	while (*var && *var != '=')
	{
		if (!(ft_isalpha(*var) || *var == '_'))
			return (ft_putstr_fd("export: bad option\n", STDERR_FILENO), false);
		var += 1;
	}
	return (true);
}

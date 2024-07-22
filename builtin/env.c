/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:08:50 by nreichel          #+#    #+#             */
/*   Updated: 2024/01/26 11:30:41 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(char ***env, char **var)
{
	int		i;
	int		len;
	char	*txt;
	int		step;

	i = -1;
	while (var[++i])
	{
		if (!unset_valid(var[i]))
			return (set_dollar(env, 1));
		if (ft_strncmp(var[i], "_", 2) != 0 && ft_strncmp(var[i], "?", 2) != 0)
		{
			txt = translate_quote(var[i], *env);
			step = -1;
			while ((*env)[++step])
			{
				len = ft_strlen(txt);
				if (ft_strncmp((*env)[step], txt, len) == 0
						&& ((*env)[step][len] == '=' || !(*env)[step][len]))
					env_ralloc_del(env, &step);
			}
			free(txt);
		}
	}
	set_dollar(env, 0);
}

void	update_env(char ***env, char *var, int len)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var, len) == 0
			&& ((*env)[i][len] == '=' || (*env)[i][len] == '\0'))
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(var);
			if (!(*env)[i])
				shell_exit(1, NULL);
			return ;
		}
		i += 1;
	}
}

void	add_env(char *txt, char ***env)
{
	*env = ralloc(*env);
	if (!*env)
		exit (1);
	(*env)[double_str_len(*env)] = ft_strdup(txt);
	if (!(*env)[double_str_len(*env) - 1])
		shell_exit(1, NULL);
}

int	export_one(char ***env, char *str, bool admin)
{
	int		len;
	char	*check;
	char	*txt;

	len = 0;
	txt = translate_quote(str, *env);
	while (txt[len] && txt[len] != '=')
		len += 1;
	if (env_var_valid(txt, admin))
	{
		check = check_env(*env, txt, len);
		if (check == NULL)
			add_env(txt, env);
		else
			update_env(env, txt, len);
		if (!admin)
			set_dollar(env, 0);
		free(txt);
		return (1);
	}
	if (!admin)
		set_dollar(env, 1);
	return (free(txt), 0);
}

void	export(char ***env, char **var, bool admin)
{
	int		i;

	i = 0;
	if (*var)
		while (var[i] && export_one(env, var[i], admin))
			i += 1;
	else
		display_env(env, true);
}

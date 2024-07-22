/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:33:16 by nreichel          #+#    #+#             */
/*   Updated: 2024/01/23 09:42:58 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_pwd_env(char *oldpwd, char ***env)
{
	char	*pwd;
	char	dir[256];

	pwd = ft_strjoin("PWD=", getcwd(dir, 256));
	if (!pwd)
		shell_exit(1, NULL);
	export_one(env, pwd, true);
	export_one(env, oldpwd, true);
	free_two(pwd, oldpwd);
}

void	set_new_directory(char **directory, char *str, char ***env)
{
	char	*oldpwd;
	char	dir[256];

	if (!str || ft_strncmp(str, "~", 2) == 0)
		str = check_env(*env, "HOME", 4);
	if (str)
	{
		if (getcwd(dir, 256) != NULL)
		{
			oldpwd = ft_strjoin("OLDPWD=", dir);
			if (!oldpwd)
				shell_exit(1, NULL);
		}
		str = translate_quote(str, *env);
		if (chdir(str) != 0)
		{
			perror("cd");
			return (set_dollar(env, 1), free_two(str, oldpwd));
		}
		if (getcwd(*directory, 256) == NULL)
			perror("cd");
		free(str);
		set_pwd_env(oldpwd, env);
	}
	set_dollar(env, 0);
}

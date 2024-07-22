/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:24:49 by nreichel          #+#    #+#             */
/*   Updated: 2024/01/30 14:12:35 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_to_child(char *pathname, char **argv, char ***env, t_sep *sep)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		shell_exit(EXIT_FAILURE, "fork");
	if (pid != 0)
	{
		sigactive(1);
		waitpid(pid, &status, 0);
		sigactive(0);
		if (WIFEXITED(status))
			set_dollar(env, WEXITSTATUS(status));
		else
			set_dollar(env, 1);
		return ;
	}
	if (sep->file_out)
		handle_outfile(sep);
	if (sep->file_in)
		handle_infile(sep);
	execve(pathname, translate_for_exec(argv, env), *env);
}

int	is_builtin(char *txt)
{
	return (ft_strncmp(txt, "echo", 5) == 0 || ft_strncmp(txt, "pwd", 4) == 0
		|| ft_strncmp(txt, "exit", 5) == 0 || ft_strncmp(txt, "export", 7) == 0
		|| (ft_strncmp(txt, "setenv", 7) == 0) || ft_strncmp(txt, "unset",
			6) == 0 || (ft_strncmp(txt, "unsetenv", 9) == 0) || ft_strncmp(txt,
			"env", 4) == 0 || ft_strncmp(txt, "cd", 3) == 0);
}

void	exec_builtin(t_sep *sep, char **directory, char ***env, char *txt)
{
	if (sep->file_out)
		handle_outfile(sep);
	if (ft_strncmp(txt, "echo", 5) == 0)
		echo(&sep->arg[1], env);
	else if (ft_strncmp(txt, "pwd", 4) == 0)
		printf("%s\n", *directory);
	else if (ft_strncmp(txt, "exit", 5) == 0)
		exit_cmd(&sep->arg[1], env);
	else if (ft_strncmp(txt, "export", 7) == 0 || (ft_strncmp(txt, "setenv",
				7) == 0))
		export(env, &sep->arg[1], false);
	else if (ft_strncmp(txt, "unset", 6) == 0 || (ft_strncmp(txt, "unsetenv",
				9) == 0))
		unset(env, &sep->arg[1]);
	else if (ft_strncmp(txt, "env", 4) == 0)
		display_env(env, false);
	else if (ft_strncmp(txt, "cd", 3) == 0)
		set_new_directory(directory, sep->arg[1], env);
	dup2(0, STDOUT_FILENO);
}

void	execute(char **input, char **directory, char ***env, t_sep *sep)
{
	char	*txt;
	char	*path;

	txt = translate_quote(input[0], *env);
	if (txt)
	{
		path = find_path(txt, *env);
		if (is_builtin(txt))
			exec_builtin(sep, directory, env, txt);
		else if (path)
			execve_to_child(path, input, env, sep);
		else if (!(ft_strncmp(txt, "<<", 3) == 0))
			no_cmd(txt, env);
		free(path);
		free(txt);
	}
}

void	execute_all(t_exec *to_run, char **directory, char ***env)
{
	if (!process_heredocs(to_run, env))
		return ;
	if (ft_strncmp(to_run->separator->pipe, "|", 1) == 0)
		pipeline(to_run, directory, env);
	else
		execute(to_run->separator->arg, directory, env, to_run->separator);
	unlink("heredoc.tmp");
}

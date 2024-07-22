/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:55:05 by nreichel          #+#    #+#             */
/*   Updated: 2024/01/29 11:03:09 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_outfile(t_sep *sep)
{
	int	fd_out;

	fd_out = -1;
	if (ft_strncmp(sep->rd_out, ">>", 2) == 0)
		fd_out = open(sep->file_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (ft_strncmp(sep->rd_out, ">", 1) == 0)
		fd_out = open(sep->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror(RED "Failed to open output file" RST);
		shell_exit(EXIT_FAILURE, NULL);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror(RED "Failed to duplicate file descriptor" RST);
		shell_exit(EXIT_FAILURE, NULL);
	}
	close(fd_out);
	return (EXIT_SUCCESS);
}

int	append_infile(t_sep *sep)
{
	int	fd_in;

	fd_in = -1;
	if (sep->rd_in != NULL)
	{
		fd_in = open(sep->file_in, O_RDONLY);
		if (fd_in == -1)
		{
			perror(RED "Failed to open input file" RST);
			shell_exit(EXIT_FAILURE, NULL);
		}
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror(RED "Failed to duplicate input file descriptor" RST);
			close(fd_in);
			shell_exit(EXIT_FAILURE, NULL);
		}
		close(fd_in);
	}
	return (EXIT_SUCCESS);
}

void	redirect_stdin_stdout(int fd_in, int fd_out)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2 for stdin");
		return ;
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2 for stdout");
		return ;
	}
	if (close(fd_in) == -1)
	{
		perror("close fd_in");
	}
	if (close(fd_out) == -1)
	{
		perror("close fd_out");
	}
}

void	process_files(t_sep *sep, int *fd_in, int *fd_out)
{
	*fd_in = STDIN_FILENO;
	*fd_out = STDOUT_FILENO;
	if (sep->file_in)
		append_infile(sep);
	if (sep->file_out)
		append_outfile(sep);
}

void	exec_redir_in_child(t_sep *sep, char *pathname, char **argv, char **env)
{
	pid_t	pid;
	int		fd_in;
	int		fd_out;
	char	*txt;

	txt = translate_quote(argv[0], env);
	process_files(sep, &fd_in, &fd_out);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		redirect_stdin_stdout(fd_in, fd_out);
		if (is_builtin(txt))
			exec_builtin(sep, &pathname, &env, txt);
		else
			execve(pathname, argv, env);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
	free(txt);
}

// void	exec_redir_in(t_sep *sep, char *pathname, char **argv, char **env)
// {
// 	pid_t	pid;
// 	int		fd;

// 	if (sep->file_in)
// 		if ((fd = open(sep->file_in, O_RDONLY)) == -1)
// 			shell_exit(EXIT_FAILURE);
// 	pid = fork();
// 	if (pid == -1)
// 		shell_exit(EXIT_FAILURE);
// 	if (pid == 0)
// 	{
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 		execve(pathname, argv, env);
// 		perror("execve");
// 		shell_exit(EXIT_FAILURE);
// 	}
// 	else
// 		waitpid(pid, NULL, 0);
// }

// void	exec_redir_out_pipe(t_sep *sep, char *pathname, char **argv, char **env)
// {
// 	pid_t	pid;
// 	int		fd_in;

// 	if (sep->file_in)
// 	{
// 		if ((fd_in = open(sep->file_in, O_RDONLY)) == -1)
// 			shell_exit(EXIT_FAILURE);
// 		if (dup2(fd_in, STDIN_FILENO) == -1)
// 			shell_exit(EXIT_FAILURE);
// 		close(fd_in);
// 	}
// 	if (sep->file_out)
// 	{
// 		if (ft_strncmp(sep->rd_out, ">>", 2) == 0)
// 			append_outfile(sep);
// 		else if (ft_strncmp(sep->rd_out, ">", 1) == 0)
// 			if (handle_outfile(sep) != EXIT_SUCCESS)
// 				shell_exit(EXIT_FAILURE);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror(RED "Failed to fork" RST);
// 		shell_exit(EXIT_FAILURE);
// 	}
// 	if (pid == 0)
// 	{
// 		if (execve(pathname, argv, env) == -1)
// 		{
// 			perror(RED "Failed to execute command" RST);
// 			shell_exit(EXIT_FAILURE);
// 		}
// 	}
// 	else
// 		waitpid(pid, NULL, 0);
// }
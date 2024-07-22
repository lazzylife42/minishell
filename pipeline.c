/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:54:59 by smonte-e          #+#    #+#             */
/*   Updated: 2024/01/30 14:10:14 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(int *fd, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		close(fd[i]);
}

void	pipe_init(int *i, int **fd, int *cmd_len, t_exec *to_run)
{
	int	j;

	j = 0;
	*cmd_len = count_pipe(to_run);
	*fd = malloc((2 * *cmd_len) * sizeof(int));
	if (!(*fd))
		shell_exit(1, NULL);
	j = -1;
	while (++j < *cmd_len)
		if (pipe(*fd + j * 2) < 0)
			shell_exit(1, "couldn't pipe");
	*i = 0;
}

void	close_and_wait(int *fd, int cmd_len)
{
	int	i;

	close_pipe(fd, 2 * cmd_len);
	i = -1;
	while (++i < cmd_len)
		wait(NULL);
	free(fd);
}

void	pipeline(t_exec *to_run, char **directory, char ***env)
{
	pid_t	pid;
	int		cmd_len;
	int		*fd;
	int		i;

	pipe_init(&i, &fd, &cmd_len, to_run);
	while (to_run)
	{
		pid = fork();
		if (pid < 0)
			shell_exit(1, "fork");
		else if (pid == 0)
		{
			if (to_run->next && dup2(fd[i + 1], 1) < 0)
				exit(1);
			if (i != 0 && dup2(fd[i - 2], 0) < 0)
				exit(1);
			close_pipe(fd, 2 * cmd_len - 1);
			execute(to_run->separator->arg, directory, env, to_run->separator);
			return (free(fd), exit(0));
		}
		to_run = to_run->next;
		i += 2;
	}
	close_and_wait(fd, cmd_len);
}

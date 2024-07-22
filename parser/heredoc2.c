/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:56:18 by nreichel          #+#    #+#             */
/*   Updated: 2024/01/30 10:17:08 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_nl(const char *delimiter)
{
	char	*line;
	char	*heredoc_txt;

	heredoc_txt = NULL;
	while (1)
	{
		line = readline(YL "heredoc> " RST);
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			if (!heredoc_txt)
				heredoc_txt = "\a";
			break ;
		}
		heredoc_txt = ralloc_str(heredoc_txt, ft_strjoin(line, "\n"),
				ft_strlen(line) + 1);
		if (!heredoc_txt)
			shell_exit(1, NULL);
		add_history(line);
		free(line);
	}
	return (heredoc_txt);
}

void	heredoc_child(char *heredoc_txt, const char *delimiter, int *fd)
{
	sigactive(3);
	close(fd[0]);
	heredoc_txt = heredoc_nl(delimiter);
	ft_putstr_fd(heredoc_txt, fd[1]);
	close(fd[1]);
	exit(0);
}

char	*heredoc(const char *delimiter)
{
	char	*heredoc_txt;
	pid_t	pid;
	int		fd[2];
	char	val;

	sigactive(2);
	heredoc_txt = NULL;
	if (pipe(fd) < 0)
		shell_exit(1, "pipe");
	pid = fork();
	if (pid == -1)
		shell_exit(1, "fork");
	if (pid == 0)
		heredoc_child(heredoc_txt, delimiter, fd);
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		while (read(fd[0], &val, 1) > 0)
			heredoc_txt = ralloc_str(heredoc_txt, &val, 1);
		close(fd[0]);
	}
	sigactive(0);
	return (heredoc_txt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonte-e <smonte-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 23:47:55 by smonte-e          #+#    #+#             */
/*   Updated: 2024/01/18 15:51:12 by smonte-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_append_outfile(t_sep *sep)
{
	int	fd;

	fd = -1;
	if (ft_strncmp(sep->rd_out, ">>", 2) == 0)
		fd = open(sep->file_out, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (ft_strncmp(sep->rd_out, ">", 1) == 0)
		fd = open(sep->file_out, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}

int	handle_infile(t_sep *sep)
{
	int	fd;

	fd = open(sep->file_in, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: infile: No such file or directory\n",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	handle_outfile(t_sep *sep)
{
	int	fd;

	fd = check_append_outfile(sep);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	check_redirections(t_exec *to_run)
{
	while (to_run)
	{
		if (to_run->separator->rd_out)
		{
			if (ft_strncmp(to_run->separator->rd_out, "<", 1) == 0)
			{
				if (handle_infile(to_run->separator))
					return (EXIT_FAILURE);
			}
			else if (ft_strncmp(to_run->separator->rd_out, ">", 1) == 0
				|| ft_strncmp(to_run->separator->rd_out, ">>", 2) == 0)
			{
				if (handle_outfile(to_run->separator))
					return (EXIT_FAILURE);
			}
			else if (ft_strncmp(to_run->separator->rd_out, "<<", 2) == 0)
			{
				if (handle_infile(to_run->separator))
					return (EXIT_FAILURE);
			}
		}
		to_run = to_run->next;
	}
	return (EXIT_SUCCESS);
}

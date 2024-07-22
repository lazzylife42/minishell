/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 09:41:30 by nreichel          #+#    #+#             */
/*   Updated: 2024/01/30 09:43:24 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count(char ***cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	count_pipe(t_exec *to_run)
{
	int	i;

	i = 0;
	while (to_run)
	{
		i++;
		to_run = to_run->next;
	}
	return (i);
}

t_exec	*handle_redir(t_exec *to_run)
{
	t_exec	*current;

	current = to_run;
	while (current)
	{
		if (current->separator->file_out)
			handle_outfile(current->separator);
		if (current->separator->file_in)
			handle_infile(current->separator);
		current = current->next;
	}
	return (to_run);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:17:48 by smonte-e          #+#    #+#             */
/*   Updated: 2024/01/31 10:02:38 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// gcc -g heredoc.c ../minishell.h -lft -L../libft -lreadline
#include "../minishell.h"

int	find_heredoc_position(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strncmp(args[i], "<<", 2) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	delete_heredoc(int heredoc_pos, t_sep **separator)
{
	while ((*separator)->arg[heredoc_pos])
	{
		free((*separator)->arg[heredoc_pos]);
		(*separator)->arg[heredoc_pos] = NULL;
		heredoc_pos++;
	}
}

// void	handle_heredoc(t_exec **to_run, char ***env)
// {
// 	char	*heredoc_txt;
// 	int		heredoc_fd;

// 	if (!(*to_run)->next || !(*to_run)->next->separator
// 		|| !(*to_run)->separator->arg[1])
// 	{
// 		perror("Error: separator not properly initialized.\n");
// 		return (set_dollar(env, 1));
// 	}
// 	if (!(*to_run)->next->separator->file_in)
// 		(*to_run)->next->separator->file_in = "heredoc.tmp";
// 	heredoc_txt = heredoc((*to_run)->separator->arg[1]);
// 	if (!heredoc_txt)
// 		return (set_dollar(env, 1));
// 	heredoc_fd = open((*to_run)->next->separator->file_in,
// 			O_WRONLY | O_CREAT | O_TRUNC, 0666);
// 	if (heredoc_fd == -1)
// 	{
// 		perror("Open");
// 		return (free(heredoc_txt));
// 	}
// 	ft_putstr_fd(heredoc_txt, heredoc_fd);
// 	close(heredoc_fd);
// 	free(heredoc_txt);
// }

int	arg_heredoc(t_sep **separator, char ***env)
{
	char	**args;
	char	*heredoc_txt;
	int		heredoc_pos;
	int		fd_heredoc;

	args = (*separator)->arg;
	heredoc_pos = find_heredoc_position(args);
	if (heredoc_pos == -1 || args[heredoc_pos + 1] == NULL)
		return (1);
	heredoc_txt = heredoc(args[heredoc_pos + 1]);
	if (!heredoc_txt)
		return (set_dollar(env, 1), delete_heredoc(heredoc_pos, separator), 0);
	fd_heredoc = open("heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_heredoc == -1)
	{
		perror("Erreur lors de la création du fichier heredoc.tmp");
		free(heredoc_txt);
		return (set_dollar(env, 1), delete_heredoc(heredoc_pos, separator), 0);
	}
	write(fd_heredoc, heredoc_txt, ft_strlen(heredoc_txt));
	close(fd_heredoc);
	(*separator)->file_in = "heredoc.tmp";
	free(heredoc_txt);
	return (delete_heredoc(heredoc_pos, separator), 1);
}

int	process_heredocs(t_exec *to_run, char ***env)
{
	t_exec	*current;
	int		count;

	count = 0;
	current = to_run;
	while (current != NULL)
	{
		if (current->separator != NULL)
		{
			if (!arg_heredoc(&(current->separator), env))
				return (0);
		}
		current = current->next;
	}
	return (1);
}

void	check_heredoc(char **tokens)
{
	char	*heredoc;
	char	*limiter;
	int		i;
	int		j;

	i = -1;
	heredoc = NULL;
	if (double_str_len(tokens) > 2)
	{
		while (tokens[++i])
		{
			if (ft_strncmp(tokens[i], "<<", 3) == 0 && tokens[i + 1])
			{
				heredoc = tokens[i];
				limiter = tokens[i + 1];
				j = i + 1;
				while (tokens[++j])
					tokens[j - 2] = tokens[j];
			}
		}
		if (heredoc)
			tokens[i - 2] = heredoc;
		if (heredoc)
			tokens[i - 1] = limiter;
	}
}
// void	rm_heredoc(const char *file_in)
// {
// 	if (file_in == NULL || file_in[0] == '\0')
// 		return ;
// 	if (unlink(file_in) == -1)
// 	{
// 		perror("Unlink");
// 		shell_exit(1);
// 	}
// }

// int	main(void)
// {
// 	char *heredoc_txt = heredoc("EOF");
// 	printf("Heredoc Text:\n%s\n", heredoc_txt);
// 	free(heredoc_txt);
// 	return (0);
// }
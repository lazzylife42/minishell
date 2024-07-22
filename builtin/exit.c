/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:22:39 by nreichel          #+#    #+#             */
/*   Updated: 2024/01/23 09:41:54 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_cmd(char **var, char ***env)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (var[count])
		count += 1;
	if (count == 0)
		shell_exit(0, NULL);
	else if (count > 1)
		return (ft_putstr_fd("exit: too many arguments\n",
				STDERR_FILENO), set_dollar(env, 1));
	while (var[0][i])
	{
		if (!(ft_isdigit(var[0][i]) || var[0][i] == '-'
			|| var[0][i] == '+'))
		{
			ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
			shell_exit(255, NULL);
		}
		i += 1;
	}
	shell_exit(ft_atoi(var[0]), NULL);
}

void	shell_exit(int n, char *perrorm)
{
	struct termios	old_termios;

	if (perrorm)
		perror(perrorm);
	old_termios = mem_termios(1);
	tcsetattr(0, TCSANOW, &old_termios);
	exit(n);
}

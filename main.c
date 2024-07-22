/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:15:43 by nreichel          #+#    #+#             */
/*   Updated: 2024/01/30 11:33:28 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///////////// for testing
void	display_double_str(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		printf("INPUT: \n");
		while (str[i])
		{
			printf("- %s\n", str[i]);
			i += 1;
		}
		printf("------------------ \n");
	}
}

/*Give the prompt to the user, will wait for it to write something, will
keep it in memory, will ft_split it and return it*/
char	**get_prompt(char *prompt)
{
	char	*line_read;
	char	**res;

	line_read = readline(prompt);
	if (line_read && *line_read)
	{
		add_history(line_read);
		res = minishell_split(line_read);
		free(line_read);
		return (res);
	}
	return (NULL);
}

void	minishell(char ***env, char **directory)
{
	char	**input;
	t_exec	*to_run;

	to_run = NULL;
	input = get_prompt(M"minishell> "RST);
	update_lastsig(env);
	if (input)
	{
		set_env_us(env, input[double_str_len(input) - 1]);
		to_run = parse(to_run, input);
		execute_all(to_run, directory, env);
		free_exec_list(to_run);
		to_run = NULL;
	}
	free_double_str(input);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;
	char	*directory;

	set_signal();
	(void)argc;
	(void)argv;
	directory = malloc(256);
	if (!directory)
		shell_exit(1, NULL);
	env = duplicate_env(envp);
	if (!env)
		shell_exit(1, NULL);
	if (getcwd(directory, 256) == NULL)
		perror("getcwd() error");
	while (1)
		minishell(&env, &directory);
	free_double_str(env);
	shell_exit(0, NULL);
}

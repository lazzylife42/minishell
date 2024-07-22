/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonte-e <smonte-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:23:21 by nreichel          #+#    #+#             */
/*   Updated: 2024/01/30 13:22:07 by smonte-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>

// Define ANSI escape sequences for text color

# define RST "\033[0m"
# define RED "\033[31m"
# define G "\033[32m"
# define Y "\033[33m"
# define YL "\033[1;33m"
# define B "\033[34m"
# define M "\033[1;35m"
# define C "\033[1;36m"
# define W "\033[37m"

/*		STRUCTURES		*/

typedef struct s_sep
{
	char			**arg;
	char			*rd_in;
	char			*rd_out;
	char			*file_in;
	char			*file_out;
	char			*pipe;
}					t_sep;

typedef struct s_exec
{
	t_sep			*separator;
	struct s_exec	*next;
}					t_exec;

/*  FUNCTIONS       */

void				echo(char **input, char ***inv);
void				export(char ***env, char **var, bool admin);
void				unset(char ***env, char **var);
void				set_new_directory(char **directory, char *str, char ***env);
char				*translate_quote(char *str, char **env);
char				**minishell_split(char *str);
int					double_str_len(char **str);
char				**ralloc(char **res);
char				*alloc_first(char *str, int len);
char				*alloc_re(char *res, char *str, int len);
char				*ralloc_str(char *res, char *str, int len);
void				display_double_str(char **str); // test
void				set_dollar(char ***env, int n);
void				perror_set(int err, char *str);

void				no_cmd(char *txt, char ***env);
/// EXIT

void				exit_cmd(char **var, char ***env);
void				shell_exit(int n, char *perrorm);

/// SIGNAL

struct termios		mem_termios(int n);
void				set_signal(void);
void				sighandler(int signum);
int					sigactive(int arg);
void				update_lastsig(char ***env);

/// FREE

void				free_two(char *a, char *b);
void				free_double_str(char **str);

/// ENV

int					export_one(char ***env, char *str, bool admin);
void				update_env(char ***env, char *var, int len);
void				add_env(char *txt, char ***env);
void				display_env(char ***env, bool extra);
char				**duplicate_env(char **env);

/// ENV2

char				*check_env(char **env, char *str, int len);
void				env_ralloc_del(char ***env, int *pos);
bool				env_var_valid(char *var, bool admin);
void				set_env_us(char ***env, char *txt);
int					unset_valid(char *var);

/// EXECUTE

char				**translate_for_exec(char **argv, char ***env);
void				execute_all(t_exec *to_run, char **directory, char ***env);
void				execve_to_child(char *pathname, char **argv, char ***env,
						t_sep *sep);
void				execute(char **input, char **directory, char ***env,
						t_sep *sep);
int					is_builtin(char *txt);
void				exec_builtin(t_sep *sep, char **directory, char ***env,
						char *txt);

/*		EXEC REDIR			*/

int					append_outfile(t_sep *sep);
void				redirect_stdin_stdout(int fd_in, int fd_out);

/*		PIPELINE			*/

void				pipeline(t_exec *to_run, char **directory, char ***env);
int					count_pipe(t_exec *to_run);

/*		REDIR				*/

int					handle_outfile(t_sep *sep);
int					handle_infile(t_sep *sep);

/*		HEREDOC				*/

void				handle_heredoc(t_exec **to_run, char ***env);
int					arg_heredoc(t_sep **separator, char ***env);
void				exec_heredoc(char **input, char ***env);
char				*heredoc(const char *delimiter);
int					find_heredoc_position(char **args);
int					process_heredocs(t_exec *to_run, char ***env);
void				check_heredoc(char **tokens);

/*		PARSER				*/

char				*find_path(char *argv, char **env);
char				**parse_arg(char **tokens, int pos);
t_exec				*parse(t_exec *to_run, char **tokens);
t_sep				*create(char **tk, int index, char *separator, int j);

/*		PARSER UTILS		*/

int					is_separator(char *token);
int					is_redir(char *token);
int					count_separators(char **tokens);

/*		LINKED LIST			*/

t_sep				*create_sep_node(char **arg, char **input, char *pipe,
						int pos);
t_exec				*add_to_exec_list(t_exec *head, t_sep *new_node);
void				free_exec_list(t_exec *head);
void				ft_free_split(char **arr);
void				print_to_run(t_exec *to_run);

#endif
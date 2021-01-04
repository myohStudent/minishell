/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 16:14:23 by myoh              #+#    #+#             */
/*   Updated: 2021/01/04 18:17:35 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./ft_printf/inc/ft_printf.h"
# include "./ft_printf/libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>

# define STDIN 0
# define STDOUT 1
# define STDERROR 2
# define CHARACTERS 1
# define SEMICOLON 2
# define PIPE 3
# define REDIR 4
# define DREDIR 5
# define BREDIR 6
# define LASTPIPE 7
# define LASTREDIR 8

extern int			errno;
char				*g_home_dir;
int					g_command_nb;
char				*g_input;
int					g_pipe_num;
int					g_sigexit;
int					g_flags[10];
char				**g_cmd_array;
int					g_pid;
char				**g_pipe_bin;
char				**g_envp_list;

typedef struct		s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_cmd
{
	int				cnt;
	int				argc;
	int				type;
	char			*typestr;
	char			*pipe_bin;
	char			**pipe_array;
	int				fdin;
	int				fdout;
	int				fd;
	int				input;
	int				output;
	int				hasenv;
	int				quote_type;
	int				hasquote;
	char			*command;
	char			*option;
	char			**argv;
	char			**option_av;
	struct s_list	*env_list;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_minishell
{
	char			*path;
	int				cnt;
	int				cmd_num;
	int				pipe_num;
	int				redir_num;
	int				quote[2];
	int				env_currnb;
	t_env			*env_list;
	t_env			*export_list;
	t_cmd			*cmd;
	t_cmd			*scmd;
}					t_minishell;

void				welcome_shell(void);
void				*ft_memalloc(size_t size);
void				display_prompt(void);
void				parent_signal_handler(int signo);
void				controld_exit(char *input);

/*
**	dollar_exec
*/
int					dollar_exec(t_cmd *curr, t_minishell *minishell);
int					dollar_exec_with_quote(t_cmd *curr, t_minishell *minishell);
int					dollar_question(void);
int					ft_strsearch(char *str, char c);

/*
** init.c
*/

void				get_envp(char **env, int i);
void				init_env(char **env, t_minishell *minishell,
					t_env *env_list);
void				get_path(t_env *list, t_minishell *minishell);

/*
** cmd_env.c
*/

int					print_env(t_env *env);
int					print_export(t_env *env);

/*
** cmd_export.c, cmd_export2.c
*/

void				envadd_back(t_env *list, char **newenv, t_minishell *minishell);
int					ft_cmp_to_update(t_env *list, char **split_new_env,
					t_minishell *minishell);
int					ft_strcmp(const char *s1, const char *s2);
void				cmd_export(t_cmd *curr, t_minishell *minishell);
void				copy_env(t_minishell *minishell, t_env *export_list,
					t_env *env);
int					ft_update_env(t_minishell *minishell, char **split_new_env);
void				add_new_env(t_minishell *minishell, char *new_env);

/*
** cmd_echo.c
*/
void				cmd_echo(t_cmd *curr, t_minishell *minishell);

/*
** handler_utils.c handler_utils2.c
*/

void				free_arr(char **arr);
char				*parse_space(char *s, char *space);
int					check_token(t_minishell *minishell, t_cmd *curr);
void				free_globals(void);
void				clear_scmd(t_cmd *cmd, t_minishell *minishell);
int					exceptions(char *input);

/*
** has_utils.c
*/

int					get_first_quote(char *command, int type);
int					has_pipes(char *option);
int					has_redirs(char *option);
int					has_quotes(t_cmd *new);
int					get_quote_type(t_cmd *new);
int					is_char_here(char c, char *str);
int					is_instr(char c, char *str);
int					ft_isquote(char c);

/*
** parse_utils, parse_utils2.c, parse_utils3.c
*/

void				tild_handler(t_minishell *minishell, t_cmd *curr);
char				*ft_trimchar(char *str, char c);
char				*space_trim(char *s);
void				too_many_tokens(t_minishell *minishell);
t_cmd				*parse3(t_minishell *minishell, t_cmd *curr);
void				get_cmd_argc(t_cmd *new);
t_cmd				*add_next_node(t_cmd *target, char *s, int i);
int					parse_flags(t_cmd *head, t_minishell *minishell);

/*
** cmd_unset.c
*/

void				cmd_unset(t_cmd *curr, t_minishell *minishell);

/*
** cmd_pwd.c
*/

void				cmd_pwd(t_cmd *curr, t_minishell *minishell);

/*
** cmd_cd.c
*/

int					cmd_cd(t_cmd *curr, t_minishell *minishell);

/*
** sig_handler.c
*/

int					get_fork(void);
int					set_fork(int current_fork);
void				parent_signal_handler(int signo);

/*
** cmd_handler.c
*/

int					cmd_handler(t_minishell *minishell);
int					has_pipes(char *option);
int					cmd_executer(t_minishell *minishell, t_cmd *curr);
void				clear_single_cmd(t_cmd *cmd);

/*
** cmd_handler2.c
*/

void				exec_piperedir(t_minishell *minishell);
void				create_pipe_array(t_minishell *minishell);
void				free_command(char *command);
void				close_fds(int pipe_fd[2]);
char				*add_dir(t_minishell *minishell, char *command);
void				big_pipe(int pid[2], int pipe_fd[2], char *command,
					t_minishell *minishell, t_cmd *scmd);
/*
** cmd_handler3.c
*/
int					exec_else(t_minishell *minishell, t_cmd *curr);
void				exec_redir_scmd(t_minishell *minishell);
void				exec_else2(t_minishell *minishell, t_cmd *scmd);
void				exec_scmd(t_minishell *minishell);

/*
** cmd_exit.c
*/

void				cmd_exit(t_cmd *curr, t_minishell *minishell);
void				clear_env(t_env *env);
void				exit_clear(t_cmd *curr, t_minishell *minishell);

/*
** parse_input.c
*/

int					get_argc(t_cmd *curr);
void				split_argv(t_cmd *curr);
void				set_node(t_minishell *minishell, t_cmd *new,
					char *data, int word_end);
t_cmd				*create_node(t_minishell *minishell, char *data,
					int word_len);
int					parse_cmd(t_minishell *minishell, t_cmd *cmd, char *input);

/*
** pipe_utils.c & pipe_utils2.c
*/

void				add_node(t_cmd *target, char *s);
t_cmd				*reverse_node(t_cmd *head);
int					parse_flag(t_cmd *curr, t_cmd *head, t_minishell *minishell,
					char flag);
void				delete_space_flag(char **temp, char flag);
void				flag_checker(char flag);
char				**store_commands(t_cmd *scmd, t_minishell *minishell);
char				*get_bin(t_minishell *minishell, char *command);
void				get_path(t_env *list, t_minishell *minishell);
char				*open_directory(char *path, char *command);

/*
** parse_quote.c
*/

int					ft_remove_quote(t_cmd *curr);
void				split_argv_quotes_cmd(t_cmd *curr);

/*
** quote_utils.c
*/

int					ft_isquote(char c);
int					get_first_quote(char *command, int type);
int					has_quotes(t_cmd *new);
int					get_quote_type(t_cmd *new);

/*
** redir_execute.c
*/

int					do_redir(t_minishell *minishell, t_cmd *scmd);
int					do_dredir(t_minishell *minishell, t_cmd *scmd);
int					do_bredir(t_minishell *minishell, t_cmd *scmd);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 16:14:23 by myoh              #+#    #+#             */
/*   Updated: 2020/12/20 01:20:00 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

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
# define LAST 7
# define ENVIRON 8

extern int 			errno;
char				*home_dir;
int					g_command_nb;
char				*raw_input;
int					pipe_num;
int					g_sigexit;
int					flags[10];
char				**g_cmd_array;
int					g_pid;
char				**pipe_bin;
char				**envp_list;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
} 					t_env;

typedef struct		s_cmd
{
	int				cnt;
	int				argc;
	int				type;
	char			*typestr;
	char			*pipe_bin; //execve용
	char			**pipe_array; //execve용
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
	char			**option_av; //옵션이 다중인자일 시 스페이스로 나뉜 인자를 이 이중배열에 담는다
	struct s_list	*env_list;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}							t_cmd;

typedef struct	 	s_minishell
{
	char			*path;
	int				cnt;
	int				cmd_num;
	int				pipe_num;
	int				redir_num;
	//char			**environ; // 환경변수 파이프 execve용
 // 명령어 파이프 execve용
	int				forked;
	int				quote[2];
	int				env_currnb; // current number
	t_env			*env_list; // env용 연결 리스트!
	t_env			*export_list;
	t_cmd			*cmd;
	t_cmd			*scmd; //cmd 복제
} 					t_minishell;

void		welcome_shell(void);
//void		ft_exit(void);
void		*ft_memalloc(size_t size);
void		display_prompt(void);
int		dollar_exec(t_cmd *curr, t_minishell *minishell);
int		dollar_exec_with_quote(t_cmd *curr, t_minishell *minishell);
void		parent_signal_handler(int signo);
void		controld_exit(char *input);

/*
** cmd_env.c
*/
int			print_env(t_env *env);
int	print_export(t_env *env);

/*
** cmd_export.c
*/ 
int			    ft_strcmp(const char *s1, const char *s2);
int cmd_export(t_cmd *curr, t_minishell *minishell);
/*
** cmd_echo.c
*/
void        cmd_echo(t_cmd *curr, t_minishell *minishell);

/*
** handler_utils.c
*/
int			arr_len(char **env);
void		free_arr(char **arr);
char	*parse_space(char *s, char *space);
int		check_token(t_minishell *minishell, t_cmd *curr);
//void	init_curr(t_cmd *curr);
/*
** has_utils.c
*/
int get_first_quote(char *command, int type);
int			has_pipes(char *option);
int			has_redirs(char *option);
int			has_quotes(t_cmd *new);
int get_quote_type(t_cmd *new);
int			is_char_here(char c, char *str);
int			is_instr(char c, char *str);
int			ft_isquote(char c);

/*
** parse_utils, parse_utils2.c
*/
char		*ft_trimchar(char *str, char c);
char		*space_trim(char *s);
void		parse3(t_minishell *minishell, t_cmd *curr);
/*
** cmd_unset.c
*/
void		cmd_unset(t_cmd *curr, t_minishell *minishell);

/*
** cmd_pwd.c
*/
void		cmd_pwd(t_cmd *curr, t_minishell *minishell);

/*
** cmd_cd.c
*/
int			cmd_cd(t_cmd *curr, t_minishell *minishell);

/*
** sig_handler.c
*/
int			get_fork(void);
int			set_fork(int current_fork);
void		parent_signal_handler(int signo);

/*
** cmd_handler.c
*/
int			cmd_handler(t_minishell *minishell);
int			has_pipes(char *option);
int			cmd_executer(t_minishell *minishell, t_cmd *curr);
int			exec_else(t_minishell *minishell, t_cmd *curr);
void		clear_scmd(t_cmd *cmd, t_minishell *minishell);
void		clear_single_cmd(t_cmd *cmd);

/*
** cmd_handler2.c
*/
void		exec_piperedir(t_minishell *minishell);
void			exec_else2(t_minishell *minishell, t_cmd *scmd, int pipe_fd[2]);
void		exec_scmd(t_minishell *minishell);
void	create_pipe_array(t_minishell *minishell);
void	exec_redir_scmd(t_minishell *minishell);

/*
** cmd_exit.c
*/
int			cmd_exit(t_cmd *curr, t_minishell *minishell);
void	clear_env(t_env *env);
/*
** parse_input.c
*/

int			get_argc(t_cmd *curr);
void		split_argv(t_cmd *curr);
void		set_node(t_minishell *minishell, t_cmd *new, char *data, int word_end);
t_cmd		*create_node(t_minishell *minishell, char *data, int word_len);
int			parse_cmd(t_minishell *minishell, t_cmd *cmd, char *input);

/*
**pipe_execute.c
*/
//int		exec_pipe(t_cmd *curr, t_minishell *minishell);
//void		parse_pipe(char **s);
//void	pipe_prog(t_minishell *minishell, t_cmd *scmd, int pipe_fd[2], int pipe_s[2]);

/*
** pipe_utils.c
*/
void		add_node(t_cmd *target, char *s);
t_cmd		*reverse_node(t_cmd *head);
int			parse_flag(t_cmd *curr, t_cmd *head, t_minishell *minishell, char flag);
void		delete_space_flag(char **temp, char flag);
void		flag_checker(char flag);
char	**store_commands(t_cmd *scmd, t_minishell *minishell);
char	*get_bin(t_minishell *minishell, char *command);
void	get_path(t_env *list, t_minishell *minishell);
char	*open_directory(char *path, char *command);

/*
** redir_execute.c
*/
void	redir1(t_minishell *minishell, t_cmd *cmd);
int		do_redir(t_minishell *minishell, t_cmd *scmd);
int		do_dredir(t_minishell *minishell, t_cmd *scmd);
int		do_bredir(t_minishell *minishell, t_cmd *scmd);

/*
** quote_utils.c
*/

int		which_quote(char *input, t_minishell *minishell);
void	prompt_quote(t_minishell *minishell);
int		in_quotes(char *s, int p);

#endif

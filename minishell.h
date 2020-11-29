/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 16:14:23 by myoh              #+#    #+#             */
/*   Updated: 2020/11/29 23:48:43 by myoh             ###   ########.fr       */
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
# include <limits.h>

# define STDIN 0
# define STDOUT 1
# define STDERROR 2
# define ISSPACE(x) (x == ' ' || x == '\t' || x == '\r')
# define SYMBOLS ";|<>"

# define CHARACTERS 1
# define SEMICOLON 2
# define PIPE 3
# define REDIR 4
# define DREDIR 5
# define FREDIR 6
# define LAST 7
# define ENVIRON 8
# define AND 9
# define OR 10
# define PAR_OPEN 11   // >
# define PAR_CLOSE 12 // <

char				*home_dir;
int					g_command_nb;
char				*raw_input;
char				*symbol; //parsing용
int					flags[10];
int					pipe_num;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
} 					t_env;

typedef struct		s_sym
{
		char			*str;
		int				type;
		char			*sym; 
		struct s_sym	*prev;
		struct s_sym	*next;
}							t_sym;

typedef struct		s_cmd
{
	int				argc;
	int				type;
	char			*bin;
	int				fdin;
	int				fdout;
	char			*command;
	char			*option;
	char			**argv;
	char			**option_av; //옵션이 다중인자일 시 스페이스로 나뉜 인자를 이 이중배열에 담는다
	struct s_list	*env_list;
	struct s_sym	*sym;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}							t_cmd;

typedef struct	 	s_minishell
{
	int				symbols_nb;
	char			*path;
	int				cnt;
	int				cmd_num;
	int				pipe_num;
	int				redir_num;
	char			**environ;
	int				forked;
	int				env_currnb; // current number
	t_env			*env_list; // env용 연결 리스트!
	t_env			*export_list;
	t_sym			*sym; //symbol 파싱용
	t_cmd			*cmd;
	t_cmd			*scmd; //cmd 복제
} 					t_minishell;

void		welcome_shell(void);
//void		ft_exit(void);
void		*ft_memalloc(size_t size);
void		display_prompt(void);
int		dollar_exec(t_cmd *curr, t_minishell *minishell);

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
** handler_utils.c
*/
int			arr_len(char **env);
void		free_arr(char **arr);
char	*parse_space(char *s, char *space);
int		check_separator(t_minishell *minishell, t_cmd *curr);
//void	init_curr(t_cmd *curr);
/*
** has_utils.c
*/
int			has_pipes(char *option);
int			has_redirs(char *option);
int			has_quotes(char *option);
int			is_char_here(char c, char *str);
int			is_instr(char c, char *str);
int			ft_is_alnum(int c);
int			has_env(char *str);
/*
** parse_utils.c
*/
int         is_char(char c, char *s);
int			parse_sym_detail(t_sym **sym_cmd, t_cmd *cmd);
char		*update_sym(t_minishell *minishell);
void		parse_symbols(t_minishell *minishell, t_cmd *curr);
int			recheck_sym(int i, char *str, char *temp, int sign);
void		parse2_symbols(t_minishell *minishell, t_sym **sym_cmd);

/*
** cmd_unset.c
*/
void		cmd_unset(t_cmd *curr, t_minishell *minishell);

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
/*
** cmd_handler2.c
*/
void		exec_piperedir(t_minishell *minishell);
void		exec_else2(t_minishell *minishell, t_cmd *scmd, int pipe_fd[2]);
void		exec_scmd(t_minishell *minishell);

/*
** cmd_exit.c
*/
int			cmd_exit(t_cmd *curr, t_minishell *minishell);
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
int			exec_pipe(t_cmd *curr, t_minishell *minishell);
void		parse_pipe(char **s);

/*
** pipe_utils.c
*/
void		add_node(t_cmd *target, char *s);
t_cmd		*reverse_node(t_cmd *head);
char		*space_trim(char *s);
int			parse_flag(t_cmd *curr, t_cmd *head, t_minishell *minishell, char flag);
void		delete_space_flag(char **temp, char flag);
void		flag_checker(char flag);
/*
** handler_utils2.c
*/
void		add_next_cmd(t_cmd **start, t_cmd *new);
char		*newline_copy(char *src);
void		clear_cmd_list_free(t_cmd *curr);
void		clear_cmd_list(t_cmd **start, void (*del)(void *));
void		clear_symcmd(t_sym **start, void (*del)(void *));
char		**args_to_str(t_minishell *minishell, t_cmd *curr);

/*
** redir_execute.c
*/
int			exec_redir(t_cmd *curr, t_minishell *minishell);
void		create_redir(t_minishell *minishell, t_cmd *cmd);

/*
**	redir_utils.c
*/
int			error_check(t_sym *sym);
t_sym		*create_symcmd(t_minishell *minishell, int i);
t_sym		*create_arg_sym(char *str, int type);
void		add_next_sym(t_sym **start, t_sym *new);

int			line_split(t_minishell *minishell, char *str, t_sym **start, int *i);
int			parse_sym(int i, char *str, char *splt, int sign);
int			sym_list_size(t_sym **start);

/*
** quote_utils.c
*/
int		which_quote(char *input);
void	prompt_quote(t_minishell *minishell);
int		in_quotes(char *s, int p);
int		line_escape(char *input, int i);
/*
**quote_utils2.c
*/
char	*simple_quote(char *src, int *i);
char	*no_quote(char *src, int *i, int j, int env);
char	*double_quote(char *src, int *i, int j, int env);
char	*exec_quotes(char *src, int env);
int		quote_len(char *src, int type, int env);


#endif

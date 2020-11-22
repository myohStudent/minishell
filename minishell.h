/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 16:14:23 by myoh              #+#    #+#             */
/*   Updated: 2020/11/22 23:40:15 by myoh             ###   ########.fr       */
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

char				*home_dir;
int					g_command_nb;
char				*raw_input;
char				**pipe_list;

int					flags[10];
// | 1, > 2, < 3, >> 4, ' 5, " 6, /' 7, ; 8, redirs 9, mixed 10개 
int					pipe_num;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
} 					t_env;

typedef struct		s_cmd
{
	int				argc;
	int				redir;
	int				dredir;
	char			*command;
	char			*option;
	char			**option_av; //옵션이 다중인자일 시 스페이스로 나뉜 인자를 이 이중배열에 담는다
	struct s_cmd	*next;
}							t_cmd;

typedef struct	 	s_minishell
{
	pid_t			pid;
	char			*path;
	int				cmd_num;
	int				pipe_num;
	int				redir_num;
	char			**environ;
	int				env_currnb; // current number
	t_env			*env_list; // env용 연결 리스트!
	t_env			*export_list;
	t_cmd			*cmd;
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

/*
** parse_utils.c
*/
int         is_char(char c, char *s);
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

/*
** redir_execute.c
*/
int			exec_redir(t_cmd *curr, t_minishell *minishell);

#endif

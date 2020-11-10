/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoichoi <seohchchoioi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 16:14:23 by myoh              #+#    #+#             */
/*   Updated: 2020/09/19 16:58:05 by seohchchoi         ###   ########.fr       */
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

int		g_env_max;

typedef struct s_env
{
	//int				is_added;
	char			*variable;
	char			*value;
} 					t_env;

typedef struct		s_cmd
{
	int				argc;
	char			*command;
	char			*option;
	char			**option_av; //옵션이 다중인자일 시 스페이스로 나뉜 인자를 이 이중배열에 담는다
	struct s_cmd	*next;
}					t_cmd;

typedef struct	 	s_minishell
{
	pid_t			pid;
	//char			**env_set;
	//char			**export_set;
	int				env_currnb; // current number
	int				env_nb; //initialized number
	char			*path;
	int				cmd_num;
	t_list			*env_list; // env용 연결 리스트!
	t_list			*export_list;
	t_env			env;
	t_cmd			*cmd;
} 					t_minishell;

void	welcome_shell(void);
//void	ft_exit(void);
void	*ft_memalloc(size_t size);
void	display_prompt(void);

/*
** initenv.c
*/
void init_env(char **env, t_minishell *minishell);
int	arr_len(char **env);
int		ft_before_chr(char *s, char c);
void	free_arr(char **arr);
/*
** cmd_env.c
*/
void	cmd_env(t_minishell *minishell);

/*
** cmd_unset.c
*/
void	cmd_unset(t_cmd *curr, t_minishell *minishell);

/*
** sig_handler.c
*/
int			get_fork(void);
int			set_fork(int current_fork);
void		parent_signal_handler(int signo);
/*
** cmd_handler.c
*/

int cmd_handler(t_minishell *minishell);
int	has_pipes(char *option);
int cmd_executor(t_minishell *minishell, t_cmd *curr);

/*
**
*/
int        env_index(t_minishell *minishell, char *str);
/*
** cmd_export.c
*/
int			    ft_strcmp(const char *s1, const char *s2);
int    cmd_export(t_cmd *curr, t_minishell *minishell);
void    		cpy_env(t_minishell *minishell, int j);
char	**arr_realloc(t_minishell *minishell, char *line);
/*
** export_utils.c
*/
void	ft_sort(t_list **start, int (*str_cmp)());
void	env_export_print(t_list *start_lst);
int		is_same(char *s1, char *s2);

/*
** cmd_exit.c
*/
int		cmd_exit(t_cmd *curr, t_minishell *minishell);
/*
** parse_input.c
*/

int get_argc(t_cmd *curr);
void split_argv(t_cmd *curr);
void set_node(t_minishell *minishell, t_cmd *new, char *data, int word_end);
t_cmd *create_node(t_minishell *minishell, char *data, int word_len);
void parse_cmd(t_minishell *minishell, t_cmd *cmd, char *input);

/*
pipe_execute.c
*/

int			exec_pipe(t_cmd *curr, t_minishell *minishell);

#endif

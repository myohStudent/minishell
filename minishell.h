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

#include "./libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <limits.h>

# define STDIN 0
# define STDOUT 1
# define STDERROR 2


typedef struct s_env
{
	char			**temp;
	char			*name;
	char			*value;
	void			*next;
} 					t_env;

typedef struct		s_cmd
{
	//int				argc;
	char			*command;
	char			*option;
	struct s_cmd	*next;
}					t_cmd;

typedef struct	 	s_minishell
{
	pid_t			pid;
	t_env			*env;
	char			*path;
	int				cmd_num;
	t_cmd			*cmd;
} 					t_minishell;

void	welcome_shell(void);
void	ft_exit(char **environ);
void	*ft_memalloc(size_t size);
void	display_prompt(void);

/*
** initenv.c
*/ 
void init_env(char **env, t_minishell *minishell);

/*
** sig_handler.c
*/

int			get_fork(void);
int			set_fork(int current_fork);
void		parent_signal_handler(int signo);
/*
** get_input.c
*/

void get_input(t_minishell *minishell); 

/*
** parse_input.c
*/
/*void get_argc(t_minishell *minishell, char *input);
void split_argv(t_minishell *minishell, char *input, int word_len, int i);
void split_input(t_minishell *minishell, char *input);
void parse_input(t_minishell *minishell, char *input);*/

#endif

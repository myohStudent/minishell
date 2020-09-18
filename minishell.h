/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 16:14:23 by myoh              #+#    #+#             */
/*   Updated: 2020/09/18 16:55:22 by seohchoi         ###   ########.fr       */
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

typedef struct s_env
{
	char			*name;
	char			*value;
	void			*next;

} 					t_env;

typedef struct	 	s_minishell
{
	pid_t			pid;
	t_env			*env;
	char			*path;
	char			*input;
} 					t_minishell;

void	welcome_shell(void);
//char	**initenv(int ac, char **av, char **env);
void	ft_exit(char **environ);
void	*ft_memalloc(size_t size);

#endif

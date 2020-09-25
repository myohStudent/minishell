/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 15:52:51 by myoh              #+#    #+#             */
/*   Updated: 2020/09/25 23:00:16 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "minishell.h"

static	int	check_fork = 0;

int			get_fork(void)
{
	return (check_fork);
}

int			set_fork(int current_fork)
{
	check_fork = current_fork;
	return (check_fork);
}

void		parent_signal_handler(int signo)
{
	if (get_fork() != 0)
	{
		ft_putstr_fd("\b\b  \b\b", STDOUT);
		if (SIGINT == signo)
		{
			write(1, "\n(ㅇㅅㅇ)>", 6);
			exit(1);
		}
	}
	else
	{
		if (SIGINT == signo)
		{
			write(1, "\n", 1);
			exit(1);
		}
		else if (SIGQUIT == signo)
		{
			write(1,"bye\n", 4);
			exit(1);
		}
	}
}
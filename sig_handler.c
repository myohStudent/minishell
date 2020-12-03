/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 15:52:51 by myoh              #+#    #+#             */
/*   Updated: 2020/12/03 21:17:13 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollarquestion_print(void)
{
	ft_printf("%d: command not found", g_exit);
	g_exit = 127;
}

// static	int	check_fork = 0;

// int			get_fork(void)
// {
// 	return (check_fork);
// }

// int			set_fork(int current_fork)
// {
// 	check_fork = current_fork;
// 	return (check_fork);
// }

void		parent_signal_handler(int signo)
{
	// if (get_fork() != 0)
	// {
	// 	ft_putstr_fd("\b\b  \b\b", STDOUT);
	// 	if (SIGINT == signo)
	// 		exit(1);
	// }
	// else
	
		if (SIGINT == signo)
		{
			write(1, "\b\b \b\b bye!\n", 11);
			exit(1);
		}
		else if (SIGQUIT == signo)
		{
			write(1,"\b\b \b\b bye!!\n", 12);
			exit(1);
		}
	
}
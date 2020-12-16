/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 15:52:51 by myoh              #+#    #+#             */
/*   Updated: 2020/12/16 16:25:02 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		controld_exit(char *input)
{
	free(input); 
	g_command_nb = 130;
	write(1, "\b\b \b\b exit!\n", 13);
	exit(1);
}

void		parent_signal_handler(int signo)
{	
		if (SIGINT == signo)
		{
			write(1, "\b\b  \b\b", 7);
			g_command_nb = 1;
			write(1,"\n", 1);
			display_prompt();
			g_sigexit = 1;
			//exit(1);
		}
		else if (SIGQUIT == signo)
		{
			write(1,"\b\b  \b\b", 7);
			//g_command_nb = 131;
			g_sigexit = 2;
			//exit(1);
		}
}
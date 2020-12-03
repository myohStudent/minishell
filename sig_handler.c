/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 15:52:51 by myoh              #+#    #+#             */
/*   Updated: 2020/12/03 19:45:23 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollarquestion_print(void)
{
	ft_printf("%d: command not found", g_exit);
	g_exit = 127;
}

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
			exit(1);
	}
	else
	{
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
}


// /* Callback function called for each line when accept-line executed, EOF
//    seen, or EOF character read.  This sets a flag and returns; it could
//    also call exit(3). */
// static void
// cb_linehandler (char *line)
// {
//   /* Can use ^D (stty eof) or `exit' to exit. */
//   if (line == NULL || strcmp (line, "exit") == 0)
//     {
//       if (line == 0)
//         printf ("\n");
//       printf ("exit\n");
//       /* This function needs to be called to reset the terminal settings,
//          and calling it from the line handler keeps one extra prompt from
//          being displayed. */
//       rl_callback_handler_remove ();
//       running = 0;
//     }
//   else
//     {
//       if (*line)
//         add_history (line);
//       printf ("input line: %s\n", line);
//       free (line);
//     }
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:14:48 by myoh              #+#    #+#             */
/*   Updated: 2021/01/08 23:27:11 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			free_command(char *command)
{
	if (command)
	{
		free(command);
		command = NULL;
	}
}

void			close_fds(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void			big_pipe(char *command, t_minishell *minishell, t_cmd *scmd)
{
	if (g_pid[0] == 0)
	{
		dup2(g_pipe_fd[0], 0);
		close(g_pipe_fd[1]);
		if (scmd->type != LASTPIPE && !(ft_compare(command, "exit")) && \
		!(ft_compare(command, "pwd")) && !(ft_compare(command, "unset")) && \
		!(ft_compare(command, "cd")) && !(ft_compare(command, "echo")) && \
		!(ft_compare(command, "env")) && !(ft_compare(command, "export")))
		{
			ft_printf("%s:command not found\n", scmd->command);
			exit(127);
		}
		else if (scmd->type == LASTPIPE)
		{
			exec_else(minishell, scmd);
			exit(1);
		}
		else
			exit(1);
	}
	else
	{
		close(g_pipe_fd[0]);
		wait(NULL);
	}
}

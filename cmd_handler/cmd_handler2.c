/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:14:48 by myoh              #+#    #+#             */
/*   Updated: 2021/01/03 20:59:00 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char			*add_dir(t_minishell *minishell, char *command)
{
	if (!command)
	{
		ft_printf("no command ");
		return (NULL);
	}
	if ((ft_compare(command, "pwd")))
		return (ft_strdup("pwd"));
	else if ((ft_compare(command, "echo")))
		return (ft_strdup("echo"));
	else if ((ft_compare(command, "cd")))
		return (ft_strdup("cd"));
	else if ((ft_compare(command, "unset")))
		return (ft_strdup("unset"));
	else if ((ft_compare(command, "export")))
		return (ft_strdup("export"));
	else if ((ft_compare(command, "env")))
		return (ft_strdup("env"));
	else if ((ft_compare(command, "exit")))
		return (ft_strdup("exit"));
	return (ft_strdup(command));
}

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

void			big_pipe(int pid[2], int pipe_fd[2], char *command,
		t_minishell *minishell, t_cmd *scmd)
{
	if (pid[0] == -1)
	{
		free_command(command);
		return ;
	}
	if (pid[0] == 0)
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[1]);
		if (scmd->type != LASTPIPE &&
		!(ft_compare(command, "pwd")) && !(ft_compare(command, "unset")) &&
		!(ft_compare(command, "cd")) && !(ft_compare(command, "echo")) &&
		!(ft_compare(command, "env")) && !(ft_compare(command, "export")) &&
		!(ft_compare(command, "exit")))
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
		close(pipe_fd[0]);
		wait(NULL);
	}
}

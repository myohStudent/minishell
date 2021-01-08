/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:46:41 by myoh              #+#    #+#             */
/*   Updated: 2021/01/08 12:00:22 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			create_pipe_array(t_minishell *minishell)
{
	int			i;

	i = g_pipe_num;
	if (!(g_cmd_array = (char **)malloc(sizeof(char *) * (i + 2))))
	{
		ft_printf("no array\n");
		return ;
	}
	i = 0;
	while (minishell->scmd->command && i <= g_pipe_num)
	{
		g_cmd_array[i] = ft_strdup(minishell->scmd->command);
		i++;
		if (minishell->scmd->next)
			minishell->scmd = minishell->scmd->next;
	}
	g_cmd_array[++i] = NULL;
	i = 0;
}

int				exec_else(t_minishell *minishell, t_cmd *curr)
{
	if (ft_strncmp(curr->command, "pwd\0", 4) == 0)
		cmd_pwd(curr, minishell);
	else if (ft_strncmp(curr->command, "cd\0", 3) == 0)
	{
		if (cmd_cd(curr, minishell) < 0)
			return (-1);
	}
	else if (ft_strncmp(curr->command, "echo\0", 5) == 0)
		cmd_echo(curr, minishell);
	else if (ft_strncmp(curr->command, "exit\0", 5) == 0)
		cmd_exit(curr, minishell);
	else if (ft_strncmp(curr->command, "env\0", 4) == 0)
		print_env(minishell->env_list);
	else if (ft_strncmp(curr->command, "export\0", 7) == 0)
		cmd_export(curr, minishell);
	else if (ft_strncmp(curr->command, "unset\0", 5) == 0)
		cmd_unset(curr, minishell);
	else
	{
		ft_printf("%s: command not found\n", curr->command);
		g_command_nb = 127;
	}
	return (1);
}

void			exec_else2(t_minishell *minishell, t_cmd *curr)
{
	if (ft_strncmp(curr->command, "cd\0", 3) == 0)
		cmd_cd(curr, minishell);
	else if (ft_strncmp(curr->command, "exit\0", 5) == 0)
		cmd_exit(curr, minishell);
	else if (ft_strncmp(curr->command, "env\0", 4) == 0)
		print_env(minishell->env_list);
	else if (ft_strncmp(curr->command, "export\0", 7) == 0)
		cmd_export(curr, minishell);
	else if (ft_strncmp(curr->command, "unset\0", 5) == 0)
		cmd_unset(curr, minishell);
	else if (ft_strncmp(curr->command, "pwd\0", 4) == 0)
		cmd_pwd(curr, minishell);
	else if (ft_strncmp(curr->command, "echo\0", 5) == 0)
		cmd_echo(curr, minishell);
}

void			exec_redir_scmd(t_minishell *minishell)
{
	pid_t		pid;
	t_cmd		*scmd;
	int			stat;

	scmd = minishell->scmd;
	while (scmd->command && scmd->type != LASTREDIR)
	{
		if ((pid = fork()) == 0)
		{
			if (scmd->type == REDIR && scmd->fd != -1)
				scmd->fd = do_redir(minishell, scmd);
			else if (scmd->type == BREDIR && scmd->fd != -1)
				scmd->fd = do_bredir(minishell, scmd);
			else if (scmd->type == DREDIR && scmd->fd != -1)
				scmd->fd = do_dredir(minishell, scmd);
			close(scmd->fd);
			exit(1);
		}
		waitpid(pid, NULL, 0);
		scmd = scmd->next;
	}
	g_sigexit = 0;
}

void			exec_scmd(t_minishell *minishell)
{
	int			i;
	t_cmd		*scmd;

	i = 0;
	scmd = minishell->scmd;
	while (g_pipe_num > -1 && scmd->command)
	{
		if (pipe(g_pipe_fd) < 0)
			return ;
		g_pid[0] = fork();
		if (g_pid[0] != -1)
			big_pipe(scmd->command, minishell, scmd);
		i++;
		scmd = scmd->next;
		close_fds(g_pipe_fd);
		g_pipe_num--;
	}
}

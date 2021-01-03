/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:46:41 by myoh              #+#    #+#             */
/*   Updated: 2021/01/03 21:04:32 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			create_pipe_array(t_minishell *minishell)
{
	t_cmd		*scmd;
	int			i;

	i = g_pipe_num;
	if (!(g_cmd_array = (char **)malloc(sizeof(char *) * (i + 2))))
	{
		ft_printf("no array\n");
		return ;
	}
	scmd = minishell->scmd;
	i = 0;
	while (scmd->command && i <= g_pipe_num)
	{
		g_cmd_array[i] = ft_strdup(scmd->command);
		i++;
		if (scmd->next)
			scmd = scmd->next;
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
		ft_printf("scmd:/%s/, opt:/%s/, type:/%d/ argc:/%d/\n",
			scmd->command, scmd->option, scmd->type, scmd->argc);
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
	g_sigexit = 1;
}

void			exec_scmd(t_minishell *minishell)
{
	int			pipe_fd[2];
	pid_t		pid[2];
	int			i;
	t_cmd		*scmd;
	char		*command;

	i = 0;
	scmd = minishell->scmd;
	create_pipe_array(minishell);
	while (g_cmd_array[i] && scmd->command)
	{
		command = add_dir(minishell, scmd->command);
		ft_printf("gcmd:/%s/, opt:/%s/, type:/%d/ argc:/%d/\n",
			g_cmd_array[i], scmd->option, scmd->type, scmd->argc);
		if (pipe(pipe_fd) < 0)
		{
			free_command(command);
			return ;
		}
		pid[0] = fork();
		big_pipe(pid, pipe_fd, command, minishell, scmd);
		i++;
		scmd = scmd->next;
		free_command(command);
		close_fds(pipe_fd);
	}
}

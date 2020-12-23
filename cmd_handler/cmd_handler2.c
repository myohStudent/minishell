/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:14:48 by myoh              #+#    #+#             */
/*   Updated: 2020/12/23 11:22:25 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			create_pipe_array(t_minishell *minishell)
{
	t_cmd		*scmd;
	char		*temp;
	int			i;

	i = pipe_num;
	if (!(g_cmd_array = (char **)malloc(sizeof(char *) * (i + 2))))
	{
		ft_printf("no array\n");
		return;
	}
	scmd = minishell->scmd;
	i = 0;
	while (scmd->command && i <= pipe_num)
	{
		g_cmd_array[i] = ft_strdup(scmd->command);
		i++;
		if (scmd->next)
			scmd = scmd->next;
	}
	g_cmd_array[++i] = NULL;
	i = 0;
}

void			exec_else2(t_minishell *minishell, t_cmd *curr, int pipe_fd[2])
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
		exit(0);
	else if (ft_strncmp(curr->command, "pwd\0", 4) == 0)
		cmd_pwd(curr, minishell);
	else if (ft_strncmp(curr->command, "echo\0", 5) == 0)
		cmd_echo(curr, minishell);
}

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
	return (NULL);
}

void			exec_redir_scmd(t_minishell *minishell)
{
	pid_t pid;
	t_cmd *scmd;
	int stat;

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
	g_sigexit = 1;
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

void			exec_scmd(t_minishell *minishell)
{
	int pipe_fd[2];
	pid_t pid[2];
	int i;
	t_cmd *scmd;
	char *command;

	i = 0;
	scmd = minishell->scmd;
	create_pipe_array(minishell);
	while (g_cmd_array[i] && scmd->command)
	{
		command = add_dir(minishell, scmd->command);
		//command = add_dir(minishell, g_cmd_array[i]);
		//ft_printf("gcmd:/%s/, opt:/%s/, type:/%d/\n", g_cmd_array[i], scmd->option, scmd->type);
		if (pipe(pipe_fd) < 0)
		{
			free_command(command);
			return;
		}
		if ((pid[0] = fork()) == -1)
		{
			free_command(command);
			break;
		}
		if (pid[0] == 0)
		{
			dup2(pipe_fd[0], 0);
			close(pipe_fd[1]);
			if (scmd->type != LASTPIPE &&
				!(ft_compare(command, "pwd")) && !(ft_compare(command, "unset")) &&
				!(ft_compare(command, "cd")) && !(ft_compare(command, "echo")) &&
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
			close(pipe_fd[0]);
			wait(NULL);
		}
		i++;
		scmd = scmd->next;
		free_command(command);
		close_fds(pipe_fd);
	}
	clear_scmd(minishell->scmd, minishell);
}
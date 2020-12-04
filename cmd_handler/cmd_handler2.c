/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:14:48 by myoh              #+#    #+#             */
/*   Updated: 2020/12/04 17:33:10 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_else2(t_minishell *minishell, t_cmd *curr, int pipe_fd[2])
{
//	ft_printf("exec_else2 들어옴 \n");
	if (ft_strncmp(curr->command, "pwd\0", 4) == 0 && curr->type != PIPE
		&& (!curr->prev || curr->prev->type != PIPE))
	{
		if (curr->argc == 1 || curr->option == NULL)
			ft_putstr_fd(getcwd(minishell->path, 4096), 1);
		else if (curr->option)
			ft_putstr_fd("pwd: too many arguments", 1);
		else if (curr->argc > 1)
			ft_putstr_fd(getcwd(minishell->path, 4096), 1);
		ft_putchar('\n');
	}
	else if (ft_strncmp(curr->command, "cd\0", 3) == 0 && curr->type != PIPE
		&& (!curr->prev || curr->prev->type != PIPE))
	{
		if (curr->argc == 1)
		{
			if (chdir(home_dir) < 0)
				return (-1);
		}
		else if (!curr->option)
		{
			if (chdir(home_dir) < 0)
				return (-1);
		}
		else if (curr->argc == 2)
		{
			if (chdir(curr->option) < 0) //경로가 실제 존재하는지 체크합니다.
				ft_putstr_fd("cd: no such file or directory\n", 1);
		}
		else if (curr->option)
			ft_putstr_fd("cd: too many arguments\n", 1);
	}
	else if (ft_strncmp(curr->command, "echo\0", 5) == 0)
	{
		if (curr->option && ft_strncmp(curr->option, "-n", 2) == 0)
			ft_putstr_fd(curr->option + 3, 1);
		if (curr->option && ft_strncmp(curr->option, "$?\0", 3) == 0)
			ft_printf("%d\n", g_exit);
		else
		{
			if (curr->option)
				ft_putstr_fd(curr->option, 1);
			ft_putchar('\n');
		}
	}
	else if (ft_strncmp(curr->command, "exit\0", 5) == 0)
		cmd_exit(curr, minishell);
	else if (ft_strncmp(curr->command, "env\0", 4) == 0)
		print_env(minishell->env_list);
	else if (ft_strncmp(curr->command, "export\0", 7) == 0)
		cmd_export(curr, minishell);
	else if (ft_strncmp(curr->command, "unset\0", 5) == 0)
		cmd_unset(curr, minishell);
	else if ((((curr->type != REDIR && curr->type != FREDIR && curr->type != DREDIR) &&
		((curr->next == NULL) || (curr->type == PIPE) || (curr->prev->type == PIPE))
		&& ((ft_strncmp(curr->command, "unset\0", 5) != 0) && (ft_strncmp(curr->command, "env\0", 4) != 0)
	 	&& (ft_strncmp(curr->command, "echo\0", 5) != 0) && (ft_strncmp(curr->command, "unset\0", 5) != 0) &&
	 	(ft_strncmp(curr->command, "cd\0", 3) != 0)  && (ft_strncmp(curr->command, "pwd\0", 4) != 0)))))
		ft_printf("%s: command not found\n", curr->command);
	else if ((!curr->prev || (curr->prev && !(curr->prev->type == PIPE))))
		pipe_prog(minishell, curr, pipe_fd, NULL);
	return (1);
}

void	exec_scmd(t_minishell *minishell)
{
	int i = 0;
	t_cmd	*scmd;
	int		pipe_fd[2];

	scmd = minishell->scmd;
	while (scmd && i < minishell->cnt)
	{
		scmd->fdin = 0;
		scmd->fdout = 0;
		redir1(minishell, scmd);
		if (scmd->command && scmd->fdout != -1 && scmd->fdin != -1)
		{
			if (pipe(pipe_fd) < 0)
				return ;
			exec_else2(minishell, scmd, pipe_fd);
			if (pipe_fd[0])
				close(pipe_fd[0]);
			if (pipe_fd[1])
				close(pipe_fd[1]);
		}
		scmd = scmd->next;
		i++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:14:48 by myoh              #+#    #+#             */
/*   Updated: 2020/12/08 23:44:34 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			cmd_content_clear(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->command)
		free(cmd->command);
	if (cmd->option)
		free(cmd->option);
	free(cmd);
}

void			cmd_clear(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->next)
	{
		cmd_clear(cmd->next);
	}
	if (cmd->command)
		cmd_content_clear(cmd);
	free(cmd);
	cmd = NULL;
}

void	exec_else2(t_minishell *minishell, t_cmd *curr, int pipe_fd[2])
{
	if (ft_strncmp(curr->command, "cd\0", 3) == 0 && curr->type != PIPE
		&& (!curr->prev || curr->prev->type != PIPE))
		cmd_cd(curr, minishell);
	else if (ft_strncmp(curr->command, "exit\0", 5) == 0 && curr->type != PIPE 
		&& (!curr->prev || curr->prev->type != PIPE))
		cmd_exit(curr, minishell);
	//else if (ft_strncmp(curr->command, "env\0", 4) == 0)
	 //	print_env(minishell->env_list);
	else if (ft_strncmp(curr->command, "export\0", 7) == 0
		&& (curr->type == REDIR || curr->type == DREDIR || curr->type == FREDIR))
		cmd_export(curr, minishell);
	else if (ft_strncmp(curr->command, "unset\0", 5) == 0)
		cmd_unset(curr, minishell);
	else if ((!curr->prev || (curr->prev && !(curr->prev->type == PIPE))))
		pipe_prog(minishell, curr, pipe_fd, NULL);
}

void	exec_scmd(t_minishell *minishell)
{
	int		pipe_fd[2];
	int		i;
	t_cmd	*scmd;

	i = 0;
	// while (minishell->scmd->command)
	// 	minishell->scmd = minishell->scmd->prev;
	// minishell->scmd = minishell->scmd->next;
	scmd = minishell->scmd;

	while (scmd && i < minishell->cnt)
	{
		// scmd->fdin = -1;
		// scmd->fdout = -1;
		redir1(minishell, scmd);
		ft_printf("current command: /%s/ \n", scmd->command);
		if (scmd->command && scmd->fdout != -1 && scmd->fdin != -1)
		{
			if (pipe(pipe_fd) < 0)
				return ;
			exec_else2(minishell, scmd, pipe_fd);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		while (scmd->type == PIPE)
		 	scmd = scmd->next;
		scmd = scmd->next;
		i++;
	}
}

/*

	int		i;
	t_cmd	*scmd;
	t_cmd	*start;
	int		past_fdout = dup(STDOUT);
	int		past_fdin = dup(STDIN);
	start = minishell->scmd;
	while (minishell->scmd)
	{
		ft_printf("pipe");
		if (create_pipe(minishell) < 0)
			return ;
		else if (i)	
			break ;
		if (pipe_exec_cmd(scmd, minishell))
		{
			dup2(past_fdout, STDOUT);
			dup2(past_fdin, STDIN);
			break;
		}
		dup2(past_fdout, STDOUT);
		dup2(past_fdin, STDIN);
		minishell->scmd = minishell->scmd->next;
	}
	//cmd_clear(start);
	

int		pipe_exec_cmd(t_cmd *scmd, t_minishell *minishell)
{
	char	*ret;

	// if (redirections(scmd))
	// 	return (-1);
	exec_else(minishell, scmd);
	if (scmd->output > 2 && close(scmd->output) < 0)
		ft_printf("error close output.\n");
	if (scmd->input > 2 && close(scmd->input) < 0)
		ft_printf("error close input.\n");
	return (1);
}

int		create_pipe(t_minishell *minishell)
{
	t_cmd *scmd;
	scmd = minishell->scmd;
	if (scmd->type == PIPE)
	{
		int		pipe_fd[2];
		pid_t	pid;
		ft_printf(" ddd \n" );
		if (pipe(pipe_fd) < 0)
		{
			ft_printf("Pipe failed.\n");
			return (-1);
		}
		pid = fork();
		ft_printf(" fff \n" );
		if (pid < 0)
		{
			ft_printf("Pipe failed.\n");
			return (-1);
		}
		else if (pid > 0) //parent
		{
			ft_printf(" eee \n" );
			close(pipe_fd[1]);
			wait(NULL);
			scmd = scmd->next;
			scmd->input = pipe_fd[0];
			dup2(scmd->input, STDIN);
			// close(pipe_fd[0]);
		}
		else // child
		{
			ft_printf(" child \n" );

			close(pipe_fd[0]);
			scmd->output = pipe_fd[1];
			dup2(scmd->output, STDOUT);
			ft_printf(" child2 \n" );

			if (pipe_exec_cmd(scmd, minishell))
				g_command_nb = 127;
			close(pipe_fd[1]);
			exit(0);
		}
	}
	return (1);	
}
*/

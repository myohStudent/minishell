/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:14:48 by myoh              #+#    #+#             */
/*   Updated: 2020/12/12 10:51:21 by myoh             ###   ########.fr       */
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

int			do_exec_scmd(t_cmd *scmd, t_minishell *minishell)
{
	ft_printf("do_scmd\n");

	exec_else(minishell, minishell->scmd);
	if (minishell->scmd->output > 2 && close(minishell->scmd->output) < 0)
		ft_printf("error close output\n");
	if (minishell->scmd->input > 2 && close(minishell->scmd->input) < 0)
		ft_printf("error close input\n");
	return (1);
}

void	init_fd(int *fd_outold, int *fd_inold, t_cmd **start, t_cmd **scmd)
{
	*fd_outold = dup(STDOUT);
	*fd_inold = dup(STDIN);
	*start = *scmd;
}

int	last_pipe_exit(t_cmd **scmd, int fd_inold)
{
	dup2(fd_inold, STDIN);
	ft_printf("클리어 준비\n");

	cmd_clear(*scmd);
	ft_printf("cmd clear\n");
	*scmd = (*scmd)->next;
	return (2);
}

int		do_pipe2(int pipe_fd[2], t_cmd **scmd, t_minishell **minishell, int fd_inold)
{
	ft_printf("do_pipe2\n");

	if (g_pid > 0)
	{
		ft_printf("do_pipe의 parent구문\n");

		close(pipe_fd[1]);
		wait(NULL);
		if ((*minishell)->scmd->type == PIPE && !((*minishell)->scmd->next->next) &&
		!ft_strncmp((*minishell)->cmd->next->command, "exit\0", 5))
			return (last_pipe_exit(scmd, fd_inold));
		(*minishell)->scmd = (*minishell)->scmd->next;
		(*minishell)->scmd->input = pipe_fd[0];
		dup2((*minishell)->scmd->input, STDIN);
	}
	else
	{
		ft_printf("do_pipe의 else구문\n");

		close(pipe_fd[0]);
		(*minishell)->scmd->output = pipe_fd[1];
		dup2((*minishell)->scmd->output, STDOUT);
		do_exec_scmd((*minishell)->scmd, *minishell);
		close(pipe_fd[1]);
		exit(0);
	}
	return (1);
}

int		do_pipe(t_cmd **scmd, t_minishell **minishell, int fd_inold)
{
	t_cmd	*cmd;
	int		pipe_fd[2];

	ft_printf("do_pipe1\n");

	if ((*minishell)->scmd->type != PIPE)
		return (1);
	if (pipe(pipe_fd) < 0)
	{
		ft_printf("pipe failed.\n");
		g_command_nb = 1;
		return (-1);
	}
	g_pid = fork();
	if (g_pid < 0)
	{	
		ft_printf("pipe: fork failed.\n");
		g_command_nb = 1;
		return (-1);
	}
	else
		return (do_pipe2(pipe_fd, scmd, minishell, fd_inold));
}

void	exec_scmd(t_minishell *minishell)
{
	int		pipe_fd[2];
	int		i;
	int		j;
	t_cmd	*start;
	int		fd_outold;
	int		fd_inold;

	i = 0;
	//scmd = minishell->scmd;
	init_fd(&fd_outold, &fd_inold, &start, &minishell->scmd);
	//scmd = minishell->scmd;
	while (minishell->scmd)
	{
		while (minishell->scmd && minishell->scmd->type == PIPE)
		{
			ft_printf("current: /%s/\n", minishell->scmd->command);

			if ((j = do_pipe(&minishell->scmd, &minishell, fd_inold)) == 2)
			{
				ft_printf("리턴\n");
				return ;
				//return(cmd_clear(minishell->scmd)) ; //del(scmd);
			}
			else if (j)
				break ;
		}
		if (do_exec_scmd(minishell->scmd, minishell))
		{
			ft_printf("듀플리케이트\n");
			dup2(fd_outold, STDOUT);
			dup2(fd_inold, STDIN);
			ft_printf("와일문 밖으로 나가기\n");
			break ;
		}
		dup2(fd_outold, STDOUT);
		dup2(fd_inold, STDIN);
		minishell->scmd = minishell->scmd->next;
		ft_printf("next: /%s/\n", minishell->scmd->command);
	}
}
		// // scmd->fdin = -1;
		// // scmd->fdout = -1;
		// redir1(minishell, scmd);
		// ft_printf("current command: /%s/ \n", scmd->command);
		// if (scmd->command && scmd->fdout != -1 && scmd->fdin != -1)
		// {
		// 	if (pipe(pipe_fd) < 0)
		// 		return ;
		// 	exec_else2(minishell, scmd, pipe_fd);
		// 	close(pipe_fd[0]);
		// 	close(pipe_fd[1]);
		// }
		// while (scmd->type == PIPE)
		//  	scmd = scmd->next;
		// scmd = scmd->next;
	
	//ft_printf("밖 1\n");
	//cmd_clear(start);
	//ft_printf("밖 2\n");



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

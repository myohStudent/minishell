/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:14:48 by myoh              #+#    #+#             */
/*   Updated: 2020/12/14 15:48:49 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipe_array(t_minishell *minishell)
{
	t_cmd	*scmd;
	char	*temp;
	int		i;

	i = pipe_num;
	if (!(g_cmd_array = (char **)malloc(sizeof(char *) * (i + 2))))
	{	
		ft_printf("no array\n");
		return ;
	}
	scmd = minishell->scmd;
	i = 0;
	while (scmd->command && i <= pipe_num)
	{
		g_cmd_array[i] = ft_strdup(scmd->command);
		// if (scmd->option)
		// {
		// 	temp = ft_strjoin(scmd->command, " ");
		// 	g_cmd_array[i] = ft_strjoin(temp, scmd->option);
		// 	free(temp);
		// 	temp = NULL;
		// }
		i++;
		if (scmd->next)
			scmd = scmd->next;
	}
	g_cmd_array[++i] = NULL;
	i = 0;
}

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
	else
		ft_printf("%s : command not found.\n", curr->command);
	// else if ((!curr->prev || (curr->prev && !(curr->prev->type == PIPE))))
	// 	pipe_prog(minishell, curr, pipe_fd, NULL);
}


char    *add_dir(t_minishell *minishell, char *command)
{
    char    *ret;
    int     i;

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
    else if ((ft_compare(command, "unset")))
        return (ft_strdup("unset"));    
    else if ((ft_compare(command, "env")))
        return (ft_strdup("env"));
    // if (is_char_here('/', command) >= 0)
    //  return (ft_strdup(command));
    // if (!pipe_bin)
    //  return (ft_strjoin("./", command));
    // i = 0;
    // while (pipe_bin && pipe_bin[i])
    // {
    //  ret = open_directory(pipe_bin[i], command);
    //  if (ret)
    //      return (ret);
    //  i++;
    // }
    return (NULL);
}

void	exec_redir_scmd(t_minishell *minishell)
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

void    exec_scmd(t_minishell *minishell)
{
    int     pipe_fd[2];
    pid_t   pid[2];
    int     i;
    int     stat;
    t_cmd   *scmd;
    char    *command;

    g_pid = 0;
    i = 0;
    scmd = minishell->scmd;
    create_pipe_array(minishell); 
    while (g_cmd_array[i] && scmd->command)
    {
        command = add_dir(minishell, g_cmd_array[i]);
		//ft_printf("current cmd: %s\n", command);
        if (pipe(pipe_fd) < 0)
        {
            free(command);
            command = NULL;
            return ;
        }
        pid[0] = fork();
        if (pid[0] == -1)
        {
            free(command);
            command = NULL;
            perror("fork error\n");
            break;
        }
        if (pid[0] == 0)
        {
            dup2(pipe_fd[0], 0);
            close(pipe_fd[1]);
            if (scmd->type != LAST &&
                !(ft_compare(command, "pwd")) && !(ft_compare(command, "unset")) &&
                !(ft_compare(command, "cd")) && !(ft_compare(command, "echo"))
                && !(ft_compare(command, "env")))
            {
                ft_printf("%s:command not found\n", scmd->command);
				//clear_single_cmd(minishell->scmd);
                exit(127);
                //execve(command, &g_cmd_array[i], minishell->environ);
            }
            else if (scmd->type == LAST)
            {
				   exec_else(minishell, scmd);
				   //clear_single_cmd(minishell->scmd);
				   exit(127);
			}
            else
            	exit(127);
;
        }
        else
        {
            close(pipe_fd[0]);
            wait(&stat);
            //signal(SIGINT, parent_signal_handler);
        }
        i++;
        scmd = scmd->next;
        free(command);
        command = NULL;
        close(pipe_fd[0]);
        close(pipe_fd[1]);
    }
	clear_scmd(minishell->scmd, minishell);
	free_arr(g_cmd_array);
	g_cmd_array = NULL;
}
	
		//ft_printf("next: /%s/\n", minishell->scmd->command);
	// }

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

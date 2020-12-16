/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:14:48 by myoh              #+#    #+#             */
/*   Updated: 2020/12/16 15:49:09 by myoh             ###   ########.fr       */
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
    else if ((ft_compare(command, "export")))
        return (ft_strdup("export"));    
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
    t_cmd   *scmd;
    char    *command;

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
                && !(ft_compare(command, "env")) && !(ft_compare(command, "echo")))
            {
                ft_printf("%s:command not found\n", scmd->command);
                exit(127);
            }
            else if (scmd->type == LAST)
            {
				   exec_else(minishell, scmd);
				   exit(127);
			}
            else
            	exit(127);
        }
        else
        {
            close(pipe_fd[0]);
            wait(NULL);
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
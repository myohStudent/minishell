/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:14:48 by myoh              #+#    #+#             */
/*   Updated: 2020/12/07 11:10:33 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_else2(t_minishell *minishell, t_cmd *curr, int pipe_fd[2])
{
	// if (ft_strncmp(curr->command, "pwd\0", 4) == 0 && curr->type != PIPE
	// 	&& (!curr->prev || curr->prev->type != PIPE))
	// 	cmd_pwd(curr, minishell);
	if (ft_strncmp(curr->command, "cd\0", 3) == 0 && curr->type != PIPE
		&& (!curr->prev || curr->prev->type != PIPE))
	{
		if (cmd_cd(curr, minishell) < 0)
			return (-1);
	}
	else if (ft_strncmp(curr->command, "exit\0", 5) == 0 && curr->type != PIPE 
		&& (curr->prev || curr->prev->type != PIPE))
		cmd_exit(curr, minishell);
	else if (ft_strncmp(curr->command, "env\0", 4) == 0)
		print_env(minishell->env_list);
	else if (ft_strncmp(curr->command, "export\0", 7) == 0)
		cmd_export(curr, minishell);
	else if (ft_strncmp(curr->command, "unset\0", 5) == 0)
		cmd_unset(curr, minishell);
	else if ((!curr->prev || (curr->prev && !(curr->prev->type == PIPE))))
		pipe_prog(minishell, curr, pipe_fd, NULL);
	// else if ((((curr->type != REDIR && curr->type != FREDIR && curr->type != DREDIR) &&
	// 	((curr->next == NULL) || (curr->type == PIPE) || (curr->prev->type == PIPE))
	// 	&& ((ft_strncmp(curr->command, "unset\0", 5) != 0) && (ft_strncmp(curr->command, "env\0", 4) != 0)
	//  	&& (ft_strncmp(curr->command, "echo\0", 5) != 0) && (ft_strncmp(curr->command, "unset\0", 5) != 0) &&
	//  	(ft_strncmp(curr->command, "cd\0", 3) != 0)  && (ft_strncmp(curr->command, "pwd\0", 4) != 0)))))
	// 	ft_printf("%s: command not found\n", curr->command);
	return (1);
}

void	exec_scmd(t_minishell *minishell)
{
	int i;
	t_cmd	*scmd;
	int		pipe_fd[2];

	i = 0;
	scmd = minishell->scmd;
	while (scmd && i < minishell->cnt)
	{
		scmd->fdin = 0;
		scmd->fdout = 0;

		redir1(minishell, scmd);
		ft_printf("redir1 나옴\n");
		if (scmd->command && scmd->fdout != -1 && scmd->fdin != -1)
		{
			if (pipe(pipe_fd) < 0)
				return ;
			exec_else2(minishell, scmd, pipe_fd);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		if (scmd->type == PIPE)
			scmd = scmd->next;
		scmd = scmd->next;
		i++;
	}
}
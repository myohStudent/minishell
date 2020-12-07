/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:14:48 by myoh              #+#    #+#             */
/*   Updated: 2020/12/07 22:56:32 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_else2(t_minishell *minishell, t_cmd *curr, int pipe_fd[2])
{
	if (ft_strncmp(curr->command, "cd\0", 3) == 0 && curr->type != PIPE
		&& (!curr->prev || curr->prev->type != PIPE))
		cmd_cd(curr, minishell);
	else if (ft_strncmp(curr->command, "exit\0", 5) == 0 && curr->type != PIPE 
		&& (!curr->prev || curr->prev->type != PIPE))
		cmd_exit(curr, minishell);
	// else if (ft_strncmp(curr->command, "env\0", 4) == 0)
	// 	print_env(minishell->env_list);
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
	int		i;
	t_cmd	*scmd;
	t_cmd	*start;
	int		past_fdout = dup(STDOUT);
	int		past_fdin = dup(STDIN);
	start = minishell->scmd;
	while (minishell->scmd)
	{
		if (create_pipe(&minishell))
			break ;
		// if (minishell->scmd->pipe)
		// 	ft_printf("%d\n", minishell->scmd->next->input);
		if (make_and_exec_cmd(minishell))
		{
			dup2(past_fdout, STDOUT);
			dup2(past_fdin, STDIN);
			break;
		}
		// if (ret)
		// {
		// 	ft_putstr_fd(ret, 1/*minishell->scmd->output*/);
		// 	free(ret);
		// }
		dup2(past_fdout, STDOUT);
		dup2(past_fdin, STDIN);
		minishell->scmd = minishell->scmd->next;
	}
	l_lst_clear(start);




	/*int		pipe_fd[2];

	i = 0;
	scmd = minishell->scmd;
	while (scmd && i < minishell->cnt)
	{
		scmd->fdin = -1;
		scmd->fdout = -1;
		redir1(minishell, scmd);
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
	}*/
}
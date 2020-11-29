/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:33:33 by myoh              #+#    #+#             */
/*   Updated: 2020/11/29 23:51:45 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*newline_copy(char *command)
{
	int		i;
	int		j;
	char	*res;

	if (!command)
		return (NULL);
	if (is_char_here('\n', command) == -1)
		return (command);
	i = 0;
	j = 0;
	if (!(res = (char *)ft_calloc(1, ft_strlen(command))))
		exit(1); //leaks	
	while (command[i])
	{
		if (command[i] != '\n')
		{
			res[j] = command[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

char	**args_to_str(t_minishell *minishell, t_cmd *curr)
{
	char	**str;
	int		i;
	t_sym *temp;

	i = 1;
	if (!(str = ft_calloc(1, sizeof(char *) * (sym_list_size(&curr->sym) + 2))))
		exit(1); //leaks (프리안했)
	str[0] = curr->command;
	temp = curr->sym;
	while (temp)
	{
		str[i] = temp->str;
		temp = temp->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

void	clear_cmd_list_free(t_cmd *curr)
{
	ft_splitdel(&curr->argv); //args_array
	ft_strdel(&curr->command);
	ft_strdel(&curr->bin);
	ft_lstclear(&curr->env_list, free);
}

void	clear_cmd_list(t_cmd **start, void (*del)(void *))
{
	t_cmd	*temp;
	t_cmd	*temp2;
	t_sym	*args;
	t_sym	*args2;

	if (!start || !del)
		return ;
	temp = *start;
	while (temp)
	{
		clear_cmd_list_free(temp);
		args = temp->sym;
		while (args)
		{
			ft_strdel(&args->str);
			args2 = args->next;
			del(args);
			args = args2;
		}
		temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
	*start = NULL;
}

void		clear_symcmd(t_sym **start, void (*del)(void *))
{
	t_sym	*temp;
	t_sym *temp2;

	if (!start || !del)
		return ;
	temp = *start;
	while (temp)
	{
		ft_strdel(&temp->str);
		temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
	*start = NULL;
}

void	add_next_cmd(t_cmd **start, t_cmd *new)
{
	t_cmd	*old;

	if (!new || !start)
		return ;
	new->command = newline_copy(new->command);
	if (*start)
	{
		old = *start;
		while (old->next)
		{
			old->next->prev = old;
			old = old->next;
		}
		old->next = new;
		new->prev = old;
		new->next = NULL;
	}
	else
		*start = new;
}

////////////////////////////////////////////
////////////////////////////////////////////

/*
void	close_fds(int fpip[2], int spip[2])
{
	close(fpip[0]);
	close(fpip[1]);
	close(spip[1]);
	close(spip[0]);
}

void	exec_prog2(t_minishell *minishell, t_cmd *tmp, pid_t pid, int fpip[2])
{
	int		status;
	int		spip[2];

	if (pipe(spip) < 0)
		return ;
	if (tmp->type == T_PIPE)
	{
		process_args(tmp->next);
		create_redirect(minishell, tmp->next);
		while (tmp->next && !tmp->next->cmd)
		{
			process_args(tmp->next);
			create_redirect(minishell, tmp->next);
			tmp = tmp->next;
		}
		tmp->next ? exec_prog(minishell, tmp->next, fpip, spip) : 0;
	}
	close_fds(fpip, spip);
	waitpid(pid, &status, WUNTRACED);
	while (!WIFEXITED(status))
		if (!WIFSIGNALED(status) || g_minishell->quit != 0 ||
			tmp->type == T_PIPE)
			break ;
	if (WIFEXITED(status) && tmp->type != T_PIPE)
		minishell->exit = WEXITSTATUS(status);
}

void	handle_fd(t_cmd *tmp, int fpip[2], int spip[2])
{
	if (tmp->prev && tmp->prev->type == T_PIPE)
	{
		dup2(fpip[0], 0);
		close(fpip[1]);
		if (tmp->type == T_PIPE)
		{
			dup2(spip[1], 1);
			close(spip[0]);
		}
	}
	else if (tmp->type == T_PIPE)
	{
		dup2(fpip[1], 1);
		close(fpip[0]);
	}
	if (tmp->out)
	{
		dup2(tmp->out, STDOUT_FILENO);
		close(tmp->out);
	}
	if (tmp->in)
	{
		dup2(tmp->in, STDIN_FILENO);
		close(tmp->in);
	}
}

void	exec(t_minishell *minishell, t_cmd *tmp)
{
	if (ft_strequ(tmp->cmd, ECHO_CMD))
		echo_cmd(minishell, tmp);
	else if (ft_strequ(tmp->cmd, CD_CMD))
		cd_cmd(minishell, tmp);
	else if (ft_strequ(tmp->cmd, EXIT_CMD))
		exit_cmd2(minishell, tmp, 1);
	else if (ft_strequ(tmp->cmd, ENV_CMD))
		env_cmd(&minishell->env_list);
	else if (ft_strequ(tmp->cmd, PWD_CMD))
		pwd_cmd(minishell);
	else if (ft_strequ(tmp->cmd, EXPORT_CMD))
		export_cmd(minishell, tmp, 1);
	else if (ft_strequ(tmp->cmd, UNSET_CMD))
		exit(0);
	else if (tmp->cmd && minishell->env_array != NULL
		&& tmp->args_array != NULL)
	{
		execve(tmp->bin, tmp->args_array, minishell->env_array);
		handle_errno(minishell, tmp->cmd, errno);
		exit(minishell->exit);
	}
	exit(0);
}

void	exec_prog(t_minishell *minishell, t_cmd *cmd, int fpip[2], int spip[2])
{
	pid_t	pid;

	minishell->forked = 1;
	cmd->bin = get_bin(minishell, cmd->cmd);
	cmd->args_array = join_args(cmd);
	pid = fork();
	if (pid == 0)
	{
		cmd->out == -1 || cmd->in == -1 ? exit(1) : 0;
		handle_fd(cmd, fpip, spip);
		exec(minishell, cmd);
	}
	else if (pid < 0 && (minishell->exit = 128))
		strerror(errno);
	else
	{
		signal(SIGINT, degage_frr);
		cmd->cmd && !ft_strequ(cmd->cmd + 2, minishell->name)
			? signal(SIGQUIT, degage_frr) : signal(SIGQUIT, SIG_IGN);
		if (cmd->type == T_PIPE && cmd->prev && cmd->prev->type == T_PIPE
			&& !close(fpip[1]) && !close(fpip[0]))
			exec_prog2(minishell, cmd, pid, spip);
		else
			exec_prog2(minishell, cmd, pid, fpip);
	}
}
*/
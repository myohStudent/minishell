/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 02:54:57 by seohchoi          #+#    #+#             */
/*   Updated: 2021/01/04 20:23:24 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			cmd_executer(t_minishell *minishell, t_cmd *curr)
{
	if (!check_token(minishell, curr))
		return (-1);
	if (g_pipe_num > 0 || minishell->redir_num > 0)
	{
		minishell->scmd = parse3(minishell, curr);
		if (minishell->scmd && g_pipe_num > 0 && minishell->redir_num > 0)
		{
			too_many_tokens(minishell);
			return (1);
		}
		if (minishell->scmd && g_pipe_num > 0)
			exec_scmd(minishell);
		else
			exec_redir_scmd(minishell);
		if (minishell->scmd)
			clear_scmd(minishell->scmd, minishell);
	}
	else if (g_pipe_num == 0 && dollar_exec(curr, minishell) == 0)
		if (!(exec_else(minishell, curr)))
			return (-1);
	free_globals();
	return (1);
}

void		ft_clear(char *input, t_minishell *minishell,
			t_cmd *curr)
{
	clear_scmd(curr, minishell);
	curr = NULL;
	free(input);
	input = NULL;
	while (minishell->cmd)
	{
		minishell->cmd->argc = 0;
		if (minishell->cmd->command)
			free(minishell->cmd->command);
		if (minishell->cmd->option)
			free(minishell->cmd->option);
		free(minishell->cmd);
		minishell->cmd = minishell->cmd->next;
	}
	minishell->cmd = 0;
	g_sigexit = 0;
}

void		buf_init(char buf1, char buf2, char **input)
{
	buf1 = ' ';
	buf2 = '\0';
	*input = ft_strdup("");
}

int			cmd_handler(t_minishell *minishell)
{
	char		buf[2];
	char		*input;
	t_cmd		*curr;
	t_cmd		*next;
	int			b;
	struct stat	*buf_stat;

	buf_init(buf[0], buf[1], &input);
	while (buf[0] != '\n')
	{
		b = read(STDIN_FILENO, buf, 1);
		if (buf[0] != '\n')
			input = ft_strjoin_free(input, buf);
		if (fstat(b, buf_stat) < 0 && b == 0)
			controld_exit(input);
	}
	minishell->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	parse_cmd(minishell, minishell->cmd, input);
	curr = minishell->cmd->next;
	while (curr != NULL && *input != 0)
	{
		if (curr->command)
		{
			if (!(cmd_executer(minishell, curr)))
				break ;
			next = curr->next;
			if (curr->next)
				free(curr);
			curr = next;
		}
	}
	ft_clear(input, minishell, curr);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 02:54:57 by seohchoi          #+#    #+#             */
/*   Updated: 2021/01/08 11:59:45 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			cmd_executer(t_minishell *minishell, t_cmd *curr)
{
	if (!check_token(minishell, curr))
		return (-1);
	if (g_pipe_num > 0 || minishell->redir_num > 0)
	{
		parse3(minishell);
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

void		buf_init(char buf1, char buf2, char **input,
			t_minishell *minishell)
{
	buf1 = ' ';
	buf2 = '\0';
	*input = ft_strdup("");
	minishell->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	minishell->cmd->argc = 0;
	minishell->cmd->option = NULL;
	minishell->cmd->command = NULL;
}

void		controld(int b, char *input)
{
	if (fstat(b, g_stat) < 0 && b == 0)
		controld_exit(input);
}

int			cmd_handler(t_minishell *minishell)
{
	char		buf[2];
	int			b;
	t_cmd		*curr;

	buf_init(buf[0], buf[1], &g_input, minishell);
	while (buf[0] != '\n')
	{
		b = read(STDIN_FILENO, buf, 1);
		if (buf[0] != '\n')
			g_input = ft_strjoin_free(g_input, buf);
		controld(b, g_input);
	}
	parse_cmd(minishell, minishell->cmd, g_input);
	curr = minishell->cmd->next;
	while (curr != NULL)
	{
		if (curr->command)
			if (!(cmd_executer(minishell, curr)))
				break ;
		curr = curr->next;
	}
	free(g_input);
	g_input = NULL;
	clear_scmd(minishell->cmd, NULL);
	return (1);
}

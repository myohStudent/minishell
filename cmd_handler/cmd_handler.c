/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 02:54:57 by seohchoi          #+#    #+#             */
/*   Updated: 2021/01/07 17:07:43 by myoh             ###   ########.fr       */
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
		reverse_clear(minishell->scmd);
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
	clear_scmd(curr, NULL);
	free(input);
	input = NULL;
	while (minishell->cmd)
	{
		minishell->cmd->argc = 0;
		if (minishell->cmd->command)
			free(minishell->cmd->command);
		if (minishell->cmd->option)
			free(minishell->cmd->option);
		if (minishell->cmd)
			free(minishell->cmd);
		minishell->cmd = minishell->cmd->next;
	}
	minishell->cmd = 0;
	g_sigexit = 0;
}

void		buf_init(char buf1, char buf2, char **input,
			t_minishell *minishell)
{
	buf1 = ' ';
	buf2 = '\0';
	*input = ft_strdup("");
	minishell->cmd = (t_cmd *)malloc(sizeof(t_cmd));
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

	buf_init(buf[0], buf[1], &g_input, minishell);
	while (buf[0] != '\n')
	{
		b = read(STDIN_FILENO, buf, 1);
		if (buf[0] != '\n')
			g_input = ft_strjoin_free(g_input, buf);
		controld(b, g_input);
	}
	parse_cmd(minishell, minishell->cmd, g_input);
	while (minishell->cmd->next != NULL)
	{
		if (minishell->cmd->next->command)
		{
			if (!(cmd_executer(minishell, minishell->cmd->next)))
				break ;
			if (minishell->cmd->next->next)
				free(minishell->cmd->next);
			minishell->cmd->next = minishell->cmd->next->next;
		}
	}
	ft_clear(g_input, minishell, minishell->cmd->next);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 02:54:57 by seohchoi          #+#    #+#             */
/*   Updated: 2020/12/29 23:25:52 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			exec_else(t_minishell *minishell, t_cmd *curr)
{
	if (ft_strncmp(curr->command, "pwd\0", 4) == 0)
		cmd_pwd(curr, minishell);
	else if (ft_strncmp(curr->command, "cd\0", 3) == 0)
		if (cmd_cd(curr, minishell) < 0)
			return (-1);
	else if (ft_strncmp(curr->command, "echo\0", 5) == 0)
		cmd_echo(curr, minishell);
	else if (ft_strncmp(curr->command, "exit\0", 5) == 0)
		cmd_exit(curr, minishell);
	else if (ft_strncmp(curr->command, "env\0", 4) == 0)
		print_env(minishell->env_list);
	else if (ft_strncmp(curr->command, "export\0", 7) == 0)
		cmd_export(curr, minishell);
	else if (ft_strncmp(curr->command, "unset\0", 5) == 0)
		cmd_unset(curr, minishell);
	else
	{
	 	ft_printf("%s: command not found\n", curr->command);
	 	g_command_nb = 127;
	}
	return (1);
}

int			cmd_executer(t_minishell *minishell, t_cmd *curr)
{
	if (!check_token(minishell, curr))
		return (-1);
	if (pipe_num > 0 || minishell->redir_num > 0)
	{
		minishell-> scmd = parse3(minishell, curr);
		if (minishell->scmd && pipe_num > 0 && minishell->redir_num > 0)
		{
			too_many_tokens(minishell);
			return (1);
		}
		if (minishell->scmd && pipe_num > 0)
			exec_scmd(minishell);
		else 
			exec_redir_scmd(minishell);
		if (minishell->scmd)
			clear_scmd(minishell->scmd, minishell);
	}
	else if (pipe_num == 0 && dollar_exec(curr, minishell) == 0)
	{
		if (!(exec_else(minishell, curr)))
			return (-1); 
	}
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
	clear_scmd(minishell->cmd, minishell);
	minishell->cmd = 0;
	g_sigexit = 0;
}

void			buf_init(char *buf1, char *buf2, char **input)
{
	buf1= ' ';
	buf2 = '\0';
	*input = ft_strdup("");
}

int				cmd_handler(t_minishell *minishell)
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
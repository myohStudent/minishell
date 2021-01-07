/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 23:38:15 by myoh              #+#    #+#             */
/*   Updated: 2021/01/07 17:07:27 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			reverse_clear(t_cmd *cmd)
{
	clear_scmd(cmd, NULL);
	while (cmd->prev)
	{
		if (cmd->command)
		{
			free(cmd->command);
			cmd->command = NULL;
		}
		if (cmd->option)
		{
			free(cmd->option);
			cmd->option = NULL;
		}
		if (cmd->type)
			cmd->type = 0;
		cmd->fd = 0;
		cmd->argc = 0;
		cmd = cmd->prev;
	}
}

t_cmd			*reverse_node(t_cmd *head)
{
	t_cmd		*p;
	t_cmd		*q;
	t_cmd		*r;

	p = head->next;
	q = NULL;
	r = NULL;
	while (p != NULL)
	{
		r = q;
		q = p;
		p = p->next;
		q->next = r;
		head->next = q;
	}
	return (q);
	reverse_clear(p);
	reverse_clear(q);
	reverse_clear(r);
	reverse_clear(head);
}

void			delete_space_flag(char **temp, char flag)
{
	int			i;

	i = 0;
	if (*temp)
	{
		while ((*temp)[i] == ' ')
			i++;
		(*temp) = ft_strdup((*temp) + i);
		if ((*temp)[i] == flag)
			i++;
		(*temp) = ft_strdup((*temp) + i);
		while ((*temp)[i] == ' ')
			i++;
		(*temp) = ft_strdup((*temp) + i);
	}
}

void			flag_checker(char flag)
{
	if (flag)
	{
		if (flag == '>')
			g_flags[1] = 1;
		else if (flag == '|')
			g_flags[0] = 1;
		else if (flag == '<')
			g_flags[2] = 1;
		else if (flag == 3)
			g_flags[3] = 1;
	}
}

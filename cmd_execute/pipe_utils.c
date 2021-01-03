/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 23:38:15 by myoh              #+#    #+#             */
/*   Updated: 2021/01/03 20:24:14 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			add_node(t_cmd *target, char *s)
{
	t_cmd		*new;

	new->next = target->next;
	new->command = ft_strdup(s);
	target->next = new;
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

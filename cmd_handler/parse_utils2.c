/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:26:22 by myoh              #+#    #+#             */
/*   Updated: 2021/01/07 21:55:25 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			free_temp(char *temp)
{
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
}

void			last_input(char *temp, int type, t_cmd *head)
{
	char		*t;

	if (temp)
	{
		if (type == PIPE)
			type = LASTPIPE;
		else
			type = LASTREDIR;
		t = ft_trim(temp);
		add_next_node(head, t, type);
	}
	if (t)
		free_temp(t);
}

void			sub_input(char *temp3, int i, int type)
{
	free_temp(temp3);
	temp3 = ft_strdup(g_temp);
	free_temp(g_temp);
	if (type == 6)
		g_temp = ft_substr(temp3, i + 2, ft_strlen(temp3) - i - 1);
	else
		g_temp = ft_substr(temp3, i + 1, ft_strlen(temp3) - i);
	free_temp(temp3);
}

void			all_parse(t_cmd *head, char *temp2, char *temp3,
				int i)
{
	while (g_temp[++i])
	{
		while (g_temp[i] == '<' || g_temp[i] == '>' || g_temp[i] == '|')
		{
			temp2 = ft_substr(g_temp, 0, i);
			if (g_temp[i] == '>' && g_temp[i + 1] != '>')
				g_type = REDIR;
			else if (g_temp[i] == '|')
				g_type = PIPE;
			else if (g_temp[i] == '>' && g_temp[i + 1] == '>')
			{
				g_type = DREDIR;
				i++;
			}
			else
				g_type = BREDIR;
			temp3 = ft_trim(temp2);
			add_next_node(head, temp3, g_type);
			free_temp(temp2);
			sub_input(temp3, i, g_type);
			i = -1;
		}
	}
	last_input(g_temp, g_type, head);
}

int				parse_flags(t_cmd *head, t_minishell *minishell)
{
	int			i;
	char		*temp;
	char		*temp2;
	char		*temp3;

	g_temp = ft_strdup(g_input);
	i = -1;
	if (g_temp != NULL)
		all_parse(head, temp2, temp3, i);
	free_temp(g_temp);
	free_temp(temp2);
	free_temp(temp3);
	return (1);
}

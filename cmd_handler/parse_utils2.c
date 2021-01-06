/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:26:22 by myoh              #+#    #+#             */
/*   Updated: 2021/01/06 14:05:43 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			last_input(char *temp, int type, t_cmd *head)
{
	if (temp)
	{
		if (type == PIPE)
			type = LASTPIPE;
		else
			type = LASTREDIR;
		head = add_next_node(head, ft_trim(temp), type);
	}
}

void			sub_input(char *temp3, int i, int type)
{
	temp3 = ft_strdup(g_temp);
	free(g_temp);
	g_temp = NULL;
	if (type == 6)
		g_temp = ft_substr(temp3, i + 2, ft_strlen(temp3) - i - 1);
	else
		g_temp = ft_substr(temp3, i + 1, ft_strlen(temp3) - i);
	free(temp3);
	temp3 = NULL;
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
			add_next_node(head, ft_trim(temp2), g_type);
			free(temp2);
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
	if (g_temp && g_temp != NULL)
	{
		free(g_temp);
		g_temp = NULL;
	}
	if (temp2 && temp2 != NULL)
	{
		free(temp2);
		temp2 = NULL;
	}
	return (1);
}

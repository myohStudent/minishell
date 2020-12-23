/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 23:38:15 by myoh              #+#    #+#             */
/*   Updated: 2020/12/23 17:22:39 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			add_node(t_cmd *target, char *s)
{
	t_cmd 		*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
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
			flags[1] = 1;
		else if (flag == '|')
			flags[0] = 1;
		else if (flag == '<')
			flags[2] = 1;
		else if (flag == 3)
			flags[3] = 1; 
	}
}

int				parse_flag(t_cmd *curr, t_cmd *head,
					t_minishell *minishell, char flag)
{
	int			i;
	char		*temp[3];
	t_cmd		*next;

	flag_checker(flag);
	i = 0;
	temp[0] = ft_strjoin(curr->command, " ");
	temp[1] = ft_strjoin(temp[0], curr->option);
	curr = curr->next;
	head->next = NULL;
	if (temp[1] != NULL)
	{
		delete_space_flag(&temp[1], flag);
		i = 0;
		if (temp[1] != NULL)
		{
			while (temp[1][i])
			{
				while (temp[1][i] == flag && temp[1][i + 1] != '\0')
				{
					
					temp[2] = ft_substr(temp[1], 0, i);
					add_node(head, ft_trim(temp[2]));
					free(temp[2]);
					free(temp[1]);
					temp[1] = NULL;
					temp[1] = ft_substr(temp[1], i + 1, ft_strlen(temp[1]) - i);
					temp[2] = NULL;
					i = -1;
				}
				i++;
			}
			if (temp[1])
				add_node(head, ft_trim(temp[1]));
			free_arr(temp);
		}
	}
	return (1);
}
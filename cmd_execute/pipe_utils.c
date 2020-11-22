/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 23:38:15 by myoh              #+#    #+#             */
/*   Updated: 2020/11/23 00:18:46 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		add_node(t_cmd *target, char *s)
{
	t_cmd *new = (t_cmd *)malloc(sizeof(t_cmd));  
    new->next = target->next;
    new->command = ft_strdup(s);
    target->next = new;
}

t_cmd		*reverse_node(t_cmd *head)
{
    t_cmd *p;
	t_cmd *q;
	t_cmd *r;

    p = head->next;
	q = NULL;
	r = NULL;
    //q = (t_cmd *)malloc(sizeof(t_cmd));
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

char		*space_trim(char *s)
{
	int		len;
	char	*t;
	char	*end;
	char	*begin;

	begin = ft_strdup(s);
    while (*begin != '\0')
    {
        if (ft_isspace(*begin))
          	begin++;
        else
        {  
          s = ft_strdup(begin);
          break;
        }  
    }
	t = ft_strdup(s);
	len = ft_strlen(s);
	end = t + len - 1;
	while (end != t && ft_isspace(*end))
        end--;
    *(end + 1) = '\0';
    s = ft_strdup(t);
    return (s);
}
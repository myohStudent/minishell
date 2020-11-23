/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 23:38:15 by myoh              #+#    #+#             */
/*   Updated: 2020/11/23 11:50:55 by myoh             ###   ########.fr       */
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

void	delete_space_flag(char **temp, char flag)
{
	int		i;

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

int		parse_flag(t_cmd *curr, t_cmd *head, t_minishell *minishell, char flag)
{
	int		i;
	int		j;
	char		*temp;
	char		*temp2;
	char		*temp3;
	t_cmd	*next;
	
	i = 0;
	temp = ft_strjoin(curr->command, " ");
	temp = ft_strjoin(temp, curr->option);
	ft_printf("%s\n", temp);
	curr = curr->next;
	head->next = NULL;

	if (temp != NULL)
	{
		delete_space_flag(&temp, flag);
		i = 0;
		if (temp != NULL)
		{
			while (temp[i])
			{ 
				while (temp[i] == flag && temp[i + 1] != '\0')
				{
					temp2 = ft_substr(temp, 0, i);
					//option 넣는 거랑 다른 부호 파싱이 여기 들어가야 함.
					add_node(head, space_trim(temp2));
					free(temp2);
					free(temp);
					temp = ft_substr(temp, i + 1, ft_strlen(temp) - i);
					temp2 = NULL;
					i = -1;
				}
				i++;
			}
			if (temp) // 마지막 cmd
			{
				add_node(head, space_trim(temp));
				temp = NULL;
				free(temp);
			}
			free(temp2);				
		}
	}
	return (1);
}
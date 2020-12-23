/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:26:22 by myoh              #+#    #+#             */
/*   Updated: 2020/12/23 11:43:21 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char			*split_cmd(char *s)
{
	int			i;
	char		*str;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	str = malloc(sizeof(char) * i);
	str = ft_substr(s, 0, i);
	str[i] = '\0';
	return (str); 
}

char			*split_opt(char *s)
{
	int			i;
	char		*str;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	str = malloc(sizeof(char) * (ft_strlen(s) - i));
	str = ft_substr(s, i + 1, ft_strlen(s));
	if (ft_compare(str, ""))
		str = NULL;
	return (str); 
}

t_cmd			*add_next_node(t_cmd *target, char *s, int i)
{
	t_cmd		*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
    new->next = target->next;
	new->command = ft_strdup(split_cmd(s));
	new->option = ft_strdup(split_opt(s));
	new->type = i;
	if (ft_compare(new->command, "export") || ft_compare(new->command, "unset")
	|| ft_compare(new->command, "cd"))
		get_cmd_argc(new);
	new->fd = 0;
	ft_printf("cmd:/%s/ opt:/%s/ argc:/%d/\n",new->command, new->option, new->argc);
	target->next = new;
	return (target);
}

int				parse_flags(t_cmd *head, t_minishell *minishell)
{
	int			i;
	int			type;
	char		*temp;
	char		*temp2;
	char		*temp3;

	temp = ft_strdup(raw_input);
	if (temp != NULL)
	{
		i = 0;
		if (temp != NULL)
		{
			while (temp[i])
			{
				while ((temp[i] == '<' || temp[i] == '>' || temp[i] == '|')
					&& temp[i + 1] != '\0')
				{
					temp2 = ft_substr(temp, 0, i);					
					///////// type 결정하기 /////////
					if (temp[i] == '>' && temp[i + 1] != '>')
						type = REDIR;	
					else if (temp[i] == '|')
						type = PIPE;
					else if (temp[i] == '>' && temp[i + 1] == '>')
					{	
						type = DREDIR;
						i++;
					}
					else
						type = BREDIR;
					add_next_node(head, ft_trim(temp2), type);
					minishell->cnt++;
					free(temp2);
					temp3 = ft_strdup(temp);
					free(temp);
					temp = NULL;
					if (type == 6)
						temp = ft_substr(temp3, i + 2, ft_strlen(temp3) - i - 1);
					else
						temp = ft_substr(temp3, i + 1, ft_strlen(temp3) - i);
					i = -1;
					free(temp3);
				}
				i++;
			}
			if (temp)
			{
				if (type == PIPE)
					type = LASTPIPE;
				else //if (type == REDIR || type == BREDIR || type == DREDIR)
					type = LASTREDIR;
				head = add_next_node(head, ft_trim(temp), type);
				temp = NULL;
			}
		}
	}
	if (temp)
		free(temp);
	if (temp2)
		free(temp2);
	return (1);
}

void			parse3(t_minishell *minishell, t_cmd *curr)
{
	int			i;
	char		*temp;
	t_cmd		*head;
	t_cmd		*scmd;

	minishell->cnt = 1;
	curr = curr->next;
	head = (t_cmd *)malloc(sizeof(t_cmd));
	scmd = (t_cmd *)malloc(sizeof(t_cmd));
	head->next = NULL;
	i = 0;
	parse_flags(head, minishell);
	scmd = head->next;
	scmd = reverse_node(head);
	minishell->scmd = scmd;
	while (scmd != NULL)
	{
		if (scmd->next)
			scmd = scmd->next;
		else
			break ;
	}
}
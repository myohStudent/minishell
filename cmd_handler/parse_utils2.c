/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:26:22 by myoh              #+#    #+#             */
/*   Updated: 2020/12/21 12:27:43 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char			**ft_onesplit(char *s, char c)
{
	int			i;
	char		**res;

	i = 0;
	res = (char **)malloc(sizeof(char *) * 3);
	while (i < ft_strlen(s))
	{
		if (s[i] == c)
		{
			res[0] = ft_substr(s, 0, i - 1);
			res[1] = ft_substr(s, i + 1, ft_strlen(s));
			return (res);
		}
		i++;
	}
	res[0] = strdup(s);
	res[1] = NULL;
	return (res);
}

t_cmd			*add_next_node(t_cmd *target, char *s, int i)
{
	char	**str;
	char	*temp;
	t_cmd	*new;

	ft_printf("s:%s\n",s);
	new = (t_cmd *)malloc(sizeof(t_cmd));
    new->next = target->next;
	str = ft_split(s, ' ');
	if (str[2])
	{
		temp = ft_strjoin(str[1], " ");
		free(str[1]);
		str[1] = NULL;
		str[1] = ft_strjoin(temp, str[2]);
		free(temp);
		temp = NULL;
	}
	ft_printf("str[0]:/%s/ str[1]:/%s/\n", str[0], str[1]);
	if (str[1] != NULL)
	{
		new->command = ft_strdup(str[0]);
	 	new->option = ft_strdup(str[1]);
		new->fd = 0;
	}
	else
		new->command = ft_strdup(str[0]);
	if (ft_compare(new->command, "export") || ft_compare(new->command, "unset"))
		{
			if (!new->option)
				new->argc = 1;
			else
				new->argc = 42;
		}
	new->type = i;
	ft_printf("cmd:/%s/ type:/%d/ opt:/%s/ argc:/%d/\n", new->command, new->type, new->option, new->argc);
	target->next = new;
	if (str[1])
		free_arr(str);
	else
		free(str);
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
					add_next_node(head, space_trim(temp2), type);
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
				type = LAST;
				head = add_next_node(head, space_trim(temp), type);
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
	temp = ft_strjoin(curr->command, " ");
	if (curr->option)
		raw_input = ft_strjoin(temp, curr->option); // raw_input을 handler에서 이미 했던 거라 이따가 봐서 지웁시당 ㅠ
	free(temp);
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
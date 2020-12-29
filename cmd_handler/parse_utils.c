/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:48:33 by myoh              #+#    #+#             */
/*   Updated: 2020/12/29 18:09:10 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ft_trimchar(char *str, char c)
{
	int		i;
	int		currindex;
	char	*res; 

	i = 0;
	currindex = 0;
	while (str[i])
	{
		if (str[i] != c)
			currindex++;
		i++;
	}
	res = (char *)malloc(sizeof(char) * (currindex + 1));
	i = 0;
	currindex = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			res[currindex] = str[i];
			currindex++;
		}
		i++;
	}
	res[currindex] = '\0';
	return (res);
}

void		parse3(t_minishell *minishell, t_cmd *curr)
{
	int		i;
	char	*temp;
	t_cmd	*head;
	t_cmd	*scmd;

	minishell->cnt = 1;
	curr = curr->next;
	head = (t_cmd *)malloc(sizeof(t_cmd));
	scmd = (t_cmd *)malloc(sizeof(t_cmd));
	head->next = NULL;
	i = 0;
	parse_flags(head, minishell);
	scmd = head->next;
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

void		too_many_tokens(t_minishell *minishell)
{
	ft_printf("pipe와 redirection을 동시에 하지 마시오\n");
	clear_scmd(minishell->scmd, minishell);
}

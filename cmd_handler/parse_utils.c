/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:48:33 by myoh              #+#    #+#             */
/*   Updated: 2021/01/07 12:01:15 by myoh             ###   ########.fr       */
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
		if (str[i++] != c)
			currindex++;
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

void		tild_handler(t_minishell *minishell, t_cmd *curr)
{
	if (curr->option[0] == '~' && (ft_isspace(curr->option[1]) || \
	curr->option[1] == '/' || curr->option[1] == 0))
		curr->option = ft_strjoin(g_home_dir, curr->option + 1);
}

t_cmd		*parse3(t_minishell *minishell)
{
	t_cmd	*head;

	head = (t_cmd *)malloc(sizeof(t_cmd));
	head->next = NULL;
	parse_flags(head, minishell);
	return (reverse_node(head));
}

void		too_many_tokens(t_minishell *minishell)
{
	ft_printf("pipe와 redirection을 동시에 하지 마시오\n");
	clear_scmd(minishell->scmd, minishell);
}

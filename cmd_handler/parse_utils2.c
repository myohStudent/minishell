/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:26:22 by myoh              #+#    #+#             */
/*   Updated: 2020/12/24 21:48:59 by myoh             ###   ########.fr       */
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
		temp = NULL;
	}
}

void			free_temp(char *temp, char *temp2)
{
	if (temp && temp != NULL)
		free(temp);
	if (temp2 && temp2 != NULL)
		free(temp2);

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
				while (temp[i] == '<' || temp[i] == '>' || temp[i] == '|')
				{
					temp2 = ft_substr(temp, 0, i);					
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
			last_input(temp, type, head);
		}
	}
	free_temp(temp, temp2);
	return (1);
}
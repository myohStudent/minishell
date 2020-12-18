/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:26:22 by myoh              #+#    #+#             */
/*   Updated: 2020/12/18 21:17:10 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd			*add_next_node(t_cmd *target, char *s, int i)
{
	char	**str;
	char	*temp;
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
    new->next = target->next;
	str = NULL;
	str = ft_split(s, ' ');
	//ft_printf("str[0]: /%s/, str[1]: /%s/\n", str[0], str[1]);
	if (str[1] != NULL)
	{
		if ((ft_compare(str[0], "pwd")) || (ft_compare(str[0], "echo")) || (ft_compare(str[0], "cd"))
			|| (ft_compare(str[0], "env")) || (ft_compare(str[0], "export")) ||(ft_compare(str[0], "unset")))
		{
			new->command = ft_strdup(str[0]);
			new->option = ft_strdup(str[1]);
		}
		else
		{
			new->command = ft_strjoin(str[0], " ");
			temp = ft_strjoin(new->command, str[1]);
			free(new->command);
			new->command = NULL;
			new->command = ft_strdup(temp);
			new->fd = 0;
			free(temp);
			temp = NULL;
		}
	}
	else
		new->command = ft_strdup(str[0]);
	new->type = i;
	ft_printf("cmd:/%s/ type:/%d/ opt:/%s/\n", new->command, new->type, new->option);
	target->next = new;
	if (str[1])
		free_arr(str);
	else
		free(str);
	str = NULL;
	//ft_printf("target-nextcmd:/%s/, newcmd:/%s/\n", target->next->command, new->command);
	//clear_scmd(new, NULL); 여기서 프리를 어떻게 해줘야 할지 모릅니다....
	//free(new);
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
						type = DREDIR;
					else
						type = BREDIR;
					/////////////////////////////
					//option parsing도 add_next_node에서
					//ft_printf("parsing temp2:/%s/ /%s/\n", temp2, space_trim(temp2));
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
			if (temp) // 마지막 cmd
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
		raw_input = ft_strjoin(temp, curr->option);
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
		ft_printf("type:%d /%s/ ", scmd->type, scmd->command);
		if (scmd->next)
			scmd = scmd->next;
		else
			break ;
	}
	ft_printf("\n");
}

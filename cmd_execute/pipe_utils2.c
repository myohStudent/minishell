/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:33:33 by myoh              #+#    #+#             */
/*   Updated: 2020/11/28 17:51:44 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*newline_copy(char *src)
{
	int		i;
	int		j;
	char	*res;

	if (!src)
		return (NULL);
	if (is_char_here('\n', src) == -1)
		return (src);
	i = 0;
	j = 0;
	if (!(res = (char *)ft_calloc(1, ft_strlen(src))))
		exit(1); //leaks	
	while (src[i])
	{
		if (src[i] != '\n')
		{
			res[j] = src[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

void	add_next_cmd(t_cmd **start, t_cmd *new)
{
	t_cmd	*temp;

	if (!new || !start)
		return ;
	new->command = newline_copy(new->command);
	if (*start)
	{
		temp = *start;
		while (temp->next)
		{
			temp->next->prev = temp;
			temp = temp->next;
		}
		temp->next = new;
		new->prev = temp;
		new->next = NULL;
	}
	else
		*start = new;
}

char	**args_to_str(t_minishell *minishell, t_cmd *curr)
{
	char	**str;
	int		i;
	t_sym *temp;

	i = 1;
	if (!(str = ft_calloc(1, sizeof(char *) * (sym_list_size(&curr->sym_cmd) + 2))))
		exit(1); //leaks (프리안했)
	str[0] = curr->command;
	temp = curr->sym_cmd;
	while (temp)
	{
		str[i] = temp->str;
		temp = temp->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

void	clear_cmd_list_free(t_cmd *curr)
{
	ft_splitdel(&curr->argv); //args_array
	ft_strdel(&curr->command);
	ft_strdel(&curr->bin);
	ft_lstclear(&curr->env_list, free);
}

void	clear_cmd_list(t_cmd **start, void (*del)(void *))
{
	t_cmd	*temp;
	t_cmd	*temp2;
	t_sym	*args;
	t_sym	*args2;

	if (!start || !del)
		return ;
	temp = *start;
	while (temp)
	{
		clear_cmd_list_free(temp);
		args = temp->sym_cmd;
		while (args)
		{
			ft_strdel(&args->str);
			args2 = args->next;
			del(args);
			args = args2;
		}
		temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
	*start = NULL;
}
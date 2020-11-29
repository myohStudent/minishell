/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:29:54 by myoh              #+#    #+#             */
/*   Updated: 2020/11/29 23:01:02 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			sym_list_size(t_sym **start)
{
	t_sym	*temp;
	int		i;

	i = 0;
	temp = *start;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

t_sym		*create_symcmd(t_minishell *minishell, int i)
{
	t_sym	*new;

	if (!minishell->cnt)
		return (NULL);
	new = (t_sym *)malloc(sizeof(t_sym));
	new->str = ft_substr(raw_input, i - minishell->cnt, minishell->cnt);
	minishell->cnt = 0;
	return (new);
}

t_sym		*create_arg_sym(char *str, int type)
{
	t_sym	*new;

	new = (t_sym *)malloc(sizeof(t_sym)); // exception processing needed.
	new->str = ft_strdup(str);
	new->type = type;
	return (new);
}

void		add_next_sym(t_sym **start, t_sym *new)
{
	t_sym	*sym;

	if (!new || !start)
		return ;
	if (*start)
	{
		sym = *start;
		while (sym->next)
		{
			sym->next->prev = sym;
			sym = sym->next;
		}
		sym->next = new;
		new->prev = sym;
		new->next = NULL;
	}
	else
		*start = new;
	ft_printf("str: /%d/ type: %d\n", new->str, new->type);
}

int		line_split(t_minishell *minishell, char *str, t_sym **start, int *i)
{
	if (is_instr(str[*i], " \t") && !in_quotes(str, *i)
		&& !line_escape(str, *i - 1))
	{
		add_next_sym(start, create_symcmd(minishell, *i));
		(*i)++;
		return (0);
	}
	if (is_instr(str[*i], "|;<>") && !in_quotes(str, *i)
		&& !line_escape(str, *i - 1) && *i > 0 && !is_instr(str[*i - 1], "<>"))
		add_next_sym(start, create_symcmd(minishell, *i));
	return (1);
}
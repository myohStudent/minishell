/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:29:54 by myoh              #+#    #+#             */
/*   Updated: 2020/11/28 17:34:20 by myoh             ###   ########.fr       */
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
	new = ft_calloc(1, sizeof(t_sym));
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
}

//split_token2
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

int		parse_sym(int i, char *str, char *splt, int sign)
{
	if (sign == 1 && is_instr(str[i], splt) && !is_instr(str[i + 1], splt)
		&& !in_quotes(str, i) && !line_escape(str, i - 1))
		return (1);
	else if (!sign && is_instr(str[i], splt) && i > 0
		&& is_instr(str[i - 1], splt) && !in_quotes(str, i) && !line_escape(str, i - 1))
		return (1);
	else if (sign == 2 && is_instr(str[i], splt)
		&& i > 0 && is_instr(str[i - 1], splt) && !in_quotes(str, i) && !line_escape(str, i - 1))
		return (1);
	else if (sign == 3 && is_instr(str[i], splt) && !in_quotes(str, i) && !line_escape(str, i - 1))
		return (1);
	return (0);
}

void	parse_symbols(t_minishell *minishell, t_cmd *curr)
{
	int		i;
	char	*temp;
	t_sym	**start;

	temp = ft_strjoin(curr->command, " ");
	raw_input = ft_strjoin(temp, curr->option);
	free(temp);
	i = 0;
	start = &minishell->sym_cmd;
	while (raw_input[i])
	{
		if (!line_split(minishell, raw_input, start, &i))
			continue ;
		minishell->symbols_nb++;
		if (parse_sym(i, raw_input, "|;", 3) || parse_sym(i, raw_input, ">", 1)
			|| parse_sym(i, raw_input, ">", 0) || parse_sym(i, raw_input, "<", 1)
			|| parse_sym(i, raw_input, "<", 0))
			add_next_sym(start, create_symcmd(minishell, i + 1));
		i++;
	}
	if (i > 0)
	{
		add_next_sym(&minishell->sym_cmd, create_symcmd(minishell, i));
		add_next_sym(&minishell->sym_cmd, create_arg_sym("new_line", 7));
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:29:54 by myoh              #+#    #+#             */
/*   Updated: 2020/11/26 18:14:20 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		line_split(t_minishell *minishell, char *str, t_sym **start, int *i)
{
	if (is_instr(str[*i], " \t") && !in_bracket(str, *i)
		&& !is_escaped(str, *i - 1))
	{
		add_token_list(start, create_token(minishell, *i));
		(*i)++;
		return (0);
	}
	if (is_char_str(str[*i], "|;<>") && !in_bracket(str, *i)
		&& !is_escaped(str, *i - 1) && *i > 0
		&& !is_char_str(str[*i - 1], "<>"))
		add_token_list(start, create_token(minishell, *i));
	return (1);
}

void		add_next_sym(t_sym **start, t_sym *new)
{
	t_sym	*tmp;

	if (!new || !start)
		return ;
	if (*start)
	{
		tmp = *start;
		while (tmp->next)
		{
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	else
		*start = new;
}

int		parse_sym(int i, char *str, char *splt, int sign)
{
	if (sign == 1 && is_char_str(str[i], splt) && !is_char_str(str[i + 1], splt)
		&& !in_bracket(str, i) && !is_escaped(str, i - 1))
		return (1);
	else if (!sign && is_char_str(str[i], splt) && i > 0
		&& is_char_str(str[i - 1], splt) && !in_bracket(str, i)
		&& !is_escaped(str, i - 1))
		return (1);
	else if (sign == 2 && is_char_str(str[i], splt)
		&& i > 0 && is_char_str(str[i - 1], splt) && !in_bracket(str, i)
		&& !is_escaped(str, i - 1))
		return (1);
	else if (sign == 3 && is_char_str(str[i], splt) && !in_bracket(str, i)
		&& !is_escaped(str, i - 1))
		return (1);
	return (0);
}

void	parse_symbols(t_minishell *minishell, t_cmd *curr)
{
	int		i;
	char	*input;
	t_sym	**start;

	input = ft_strjoin(curr->command, curr->option);
	i = 0;
	start = &minishell->sym_cmd;
	while (input[i])
	{
		if (!line_split(minishell, input, start, &i))
			continue ;
		minishell->symbols_nb++;
		if (parse_sym(i, input, "|;", 3) || parse_sym(i, input, ">", 1)
			|| parse_sym(i, input, ">", 0) || parse_sym(i, input, "<", 1)
			|| parse_sym(i, input, "<", 0))
			add_next_sym(start, create_token(minishell, i + 1));
		i++;
	}
	if (i > 0)
	{
		add_sym_cmd(&minishell->sym_cmd, create_token(minishell, i));
		add_sym_cmd(&minishell->sym_cmd,
			create_arg_token("newline", T_NEWLINE));
	}
}
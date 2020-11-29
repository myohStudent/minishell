/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:48:33 by myoh              #+#    #+#             */
/*   Updated: 2020/11/29 00:41:51 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		error_check(t_sym *sym)
{
	if ((sym->type == PIPE || sym->type == SEMICOLON) && !sym->prev)
		return (0);
	if (sym->type == REDIR && (sym->prev
		&& sym->prev->type == REDIR))
		return (0);
	if (sym->type == NEW_LINE && sym->prev
		&& (sym->prev->type == REDIR || sym->prev->type == PIPE))
		return (0);
	if ((sym->type == PIPE || sym->type == SEMICOLON)
		&& (sym->prev->type == PIPE || sym->prev->type == SEMICOLON
		|| sym->prev->type == REDIR))
		return (0);
	return (1);
}

int         is_char(char c, char *s)
{
    int     i;

    i = 0;
    while (s[i])
    {
        if (c == s[i])
            return (i);
        i++;
    }
    return (-1);
}

char		*update_sym(t_minishell *minishell)
{
	t_sym *sym;

	sym = minishell->sym_cmd;
	while (sym)
	{
		if (ft_compare(sym->str, ">") || ft_compare(sym->str, ">>")
			|| ft_compare(sym->str, "<<") || ft_compare(sym->str, "<"))
			sym->type = REDIR;
		else if (ft_compare(sym->str, "|"))
			sym->type = PIPE;
		else if (ft_compare(sym->str, ";"))
			sym->type = SEMICOLON;
		else if (ft_compare(sym->str, "new_line") && !sym->next)
			sym->type = NEW_LINE;
		else if (has_env(sym->str))
			sym->type = ENVIRON;
		else
			sym->type = CHARACTERS;
		if (!error_check(sym))
			return (sym->str);
		ft_printf("sym->type: %d\n", sym->type);
		sym = sym->next;
	}
	return (NULL);
}
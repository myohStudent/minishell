/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:48:33 by myoh              #+#    #+#             */
/*   Updated: 2020/11/27 00:19:31 by myoh             ###   ########.fr       */
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
		sym = sym->next;
	}
	return (NULL);
}

int		parse_sym_detail(t_sym **sym_cmd, t_cmd *cmd)
{
/*if ((*sym)->type == T_WORD && (cmd->cmd || ((*sym)->prev
		&& (*sym)->prev->type == T_REDIRECT)))
		add_sym_list(&cmd->args,
			create_arg_sym((*sym)->str, (*sym)->type));
	if ((*sym)->type == T_WORD && !cmd->cmd && (((*sym)->prev
		&& (*sym)->prev->type != T_REDIRECT) || !(*sym)->prev))
		cmd->cmd = ft_strdup((*sym)->str);
	if ((*sym)->type == T_REDIRECT)
		add_sym_list(&cmd->args,
			create_arg_sym((*sym)->str, (*sym)->type));
	if ((*sym)->type == T_ENV && !cmd->cmd)
		ft_lstadd_back(&cmd->env_list, ft_lstnew(ft_strdup((*sym)->str)));
	if ((*sym)->type == T_PIPE)
	{
		cmd->type = T_PIPE;
		*sym = (*sym)->next;
		return (0);
	}
	if ((*sym)->type == T_SEP)
	{
		cmd->type = T_SEP;
		*sym = (*sym)->next;
		return (0);
	}*/
	return (1);
}

void	parse2_symbols(t_minishell *minishell, t_sym **sym_cmd)
{/*
	t_cmd	*cmd;

	if ((*sym)->type == T_NEWLINE)
	{
		*sym = (*sym)->next;
		return ;
	}
	if (!(cmd = ft_calloc(1, sizeof(t_cmd))))
		return ;
	while (*sym)
	{
		if (!parse_syms2(sym, cmd))
			break ;
		if ((*sym)->type == T_ENV && cmd->cmd)
			add_sym_list(&cmd->args,
				create_arg_sym((*sym)->str, (*sym)->type));
		*sym = (*sym)->next;
	}
	add_cmd_list(&minishell->cmd_list, cmd);*/
}
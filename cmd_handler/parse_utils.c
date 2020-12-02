/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:48:33 by myoh              #+#    #+#             */
/*   Updated: 2020/12/02 19:23:38 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int		error_check(t_sym *sym)
// {
// 	if ((sym->type == PIPE || sym->type == SEMICOLON) && !sym->prev)
// 		return (0);
// 	if (sym->type == REDIR && (sym->prev && sym->prev->type == REDIR))
// 		return (0);
// 	if (sym->type == LAST && sym->prev && (sym->prev->type == REDIR || sym->prev->type == PIPE))
// 		return (0);
// 	if ((sym->type == PIPE || sym->type == SEMICOLON) &&
// 		(sym->prev->type == PIPE || sym->prev->type == SEMICOLON || sym->prev->type == REDIR))
// 		return (0);
// 	return (1);
// }

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

/*
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

char		*update_sym(t_minishell *minishell)
{
	t_sym *sym;

	sym = minishell->sym;
	while (sym)
	{
		if (ft_compare(sym->str, ">") || ft_compare(sym->str, ">>") || ft_compare(sym->str, "<"))
			sym->type = REDIR;
		else if (ft_compare(sym->str, "|"))
			sym->type = PIPE;
		else if (ft_compare(sym->str, ";"))
			sym->type = SEMICOLON;
		else if (ft_compare(sym->str, "last") && !sym->next)
			sym->type = LAST;
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

int		recheck_sym(int i, char *str, char *temp, int sign) // 심볼이 있나 없나
{
	if (sign == 1 && is_instr(str[i], temp) && !is_instr(str[i + 1], temp)
		&& !in_quotes(str, i) && !line_escape(str, i - 1))
		return (1);
	else if (!sign && is_instr(str[i], temp) && i > 0
		&& is_instr(str[i - 1], temp) && !in_quotes(str, i) && !line_escape(str, i - 1))
		return (1);
	else if (sign == 2 && is_instr(str[i], temp)
		&& i > 0 && is_instr(str[i - 1], temp) && !in_quotes(str, i) && !line_escape(str, i - 1))
		return (1);
	else if (sign == 3 && is_instr(str[i], temp) && !in_quotes(str, i) && !line_escape(str, i - 1))
		return (1);
	return (0);
}

void	parse_symbols(t_minishell *minishell, t_cmd *curr)
{
	int		i;
	char	*temp;
	t_sym	**start;

	temp = ft_strjoin(curr->command, " ");
	if (curr->option)
		raw_input = ft_strjoin(temp, curr->option);
	free(temp);
	start = &minishell->sym;
	i = 0;
	ft_printf("raw_input: /%s/ ", raw_input);
	while (raw_input[i])
	{		
		if (!line_split(minishell, raw_input, start, &i)) //공백
			continue ;
		minishell->cnt++;
		if (recheck_sym(i, raw_input, "|;", 3) || recheck_sym(i, raw_input, ">", 1)
			|| recheck_sym(i, raw_input, ">", 0) || recheck_sym(i, raw_input, "<", 1)
			|| recheck_sym(i, raw_input, "<", 0))
			add_next_sym(start, create_symcmd(minishell, i + 1));
		i++;
	}
	if (i > 0)
	{
		add_next_sym(&minishell->sym, create_symcmd(minishell, i));
		add_next_sym(&minishell->sym, create_arg_sym("last", 7));
	}
}

int		parse_sym2(t_sym **sym, t_cmd *curr)
{
	if ((*sym)->type == CHARACTERS && (curr->command || ((*sym)->prev && (*sym)->prev->type == REDIR)))
		add_next_sym(&curr->sym, create_arg_sym((*sym)->str, (*sym)->type));
	if ((*sym)->type == CHARACTERS && !curr->command && (((*sym)->prev
		&& (*sym)->prev->type != REDIR) || !(*sym)->prev))
		curr->command = ft_strdup((*sym)->str); //명령어 넣기
	if ((*sym)->type == REDIR)
		add_next_sym(&curr->sym, create_arg_sym((*sym)->str, (*sym)->type));
	//if ((*sym)->type == ENVIRON && !curr->command)
	//	ft_lstadd_back(&curr->env_list, ft_lstnew(ft_strdup((*sym)->str)));
	if ((*sym)->type == PIPE)
	{
		curr->type = PIPE;
		*sym = (*sym)->next;
		return (0);
	}
	if ((*sym)->type == SEMICOLON)
	{
		curr->type = SEMICOLON;
		*sym = (*sym)->next;
		return (0);
	}
	return (1);
}

void	parse2_symbols(t_minishell *minishell, t_sym **sym)
{
	t_cmd	*curr;

	if ((*sym)->type == LAST)
	{
		*sym = (*sym)->next;
		return ;
	}
	if (!(curr = ft_calloc(1, sizeof(t_cmd))))
		return ;
	while (*sym)
	{
		if (!parse_sym2(sym, curr))
			break ;
		//if ((*sym)->type == ENVIRON && curr->command)
		//	add_next_sym(&curr->sym, create_arg_sym((*sym)->str, (*sym)->type));
		*sym = (*sym)->next;
	}
	add_next_cmd(&minishell->scmd, curr);
}*/
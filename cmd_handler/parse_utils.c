/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:48:33 by myoh              #+#    #+#             */
/*   Updated: 2020/11/23 20:44:49 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
char	*parse_symbols(t_minishell *minishell, t_symbol *input)
{
	t_symbol *temp;

	temp = input;
	while (temp)
	{
		if (ft_compare(temp->type, ">") || ft_compare(temp->type, ">>")
			|| ft_compare(temp, "<<") || ft_compare(temp, "<"))
			temp->type = REDIR;
		else if (ft_compare(temp, "|"))
			temp->type = PIPE;
		else if (ft_compare(temp, ";"))
			temp->type = SEMICOLON;
		//else if (ft_compare(temp, "newline") && !temp->next)
		//	temp->type = T_NEWLINE;
		//else if (is_valid_env(temp))
		//	temp->type = T_ENV;
		else
			temp->type = WORD;
		if (!check_error(temp)) //&& (minishell->exit = 258))
			return (temp->word);
		temp = temp->next;
	}
	return (NULL);
}*/
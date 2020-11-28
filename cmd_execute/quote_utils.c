/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 10:27:27 by myoh              #+#    #+#             */
/*   Updated: 2020/11/28 17:38:46 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** 34 = single quote > 
** 39 = double quote <
*/

int		line_escape(char *input, int i)
{
	int ret;

	ret = 0;
	while (i >= 0 && input[i] == '\\')
	{
		ret++;
		i--;
	}
	return (ret % 2);
}

int		in_quotes(char *s, int p)
{
	int	quote;
	int	dquote;
	int	i;

	quote = 0;
	dquote = 0;
	i = 0;
	while (i <= p)
	{
		if (s[i] == 34 && (i == 0 || !line_escape(s, i - 1))
			&& dquote % 2 == 0)
			quote++;
		if (s[i] == 39 && (i == 0 || dquote % 2 != 0 || !line_escape(s, i - 1))
			&& quote % 2 == 0)
			dquote++;
		i++;
	}
	if (quote % 2 != 0 || dquote % 2 != 0)
		return (1);
	return (0);
}

int     end_pipe(char *input, int i)
{
    while (i > 0 && (input[i] == ' ' || input[i] == '\n'))
		i--;
	if (i > 0 && input[i] == '|' && !line_escape(input, i - 1))
	{
		i = 0;
		while (input[i] && (input[i] == ' ' || input[i] == '\n'))
			i++;
		if (input[i] != '|')
		{
			while (input[i] && (input[i] != '|' || line_escape(input, i) ||
				in_quotes(input, i)))
				i++;
			if (!input[i] || !input[i + 1])
				return (1);
			else
				i++;
			while (input[i] && (input[i] == ' ' || input[i] == '\n'))
				i++;
			if (input[i] != '|')
				return (1);
		}
	}
	return (0);
}

int		which_quote(char *input)
{
    int		quote;
	int		dquote;
	int		i;
    int     r;

    i = 0;
	quote = 0;
	dquote = 0;
	r = 1;
	while (input[i])
	{
		if (input[i] == 34 && (i == 0 || !line_escape(input, i - 1))
			&& dquote % 2 == 0)
			quote++;
		if (input[i] == 39 && (i == 0 || dquote % 2 != 0 || !line_escape(input, i - 1))
			&& quote % 2 == 0)
			dquote++;
		i++;
	}
	if (quote % 2 != 0 || dquote % 2 != 0)
		return (1);
    if (r)
        return (end_pipe(input, i - 1));
    return (0);
}

void	prompt_quote(t_minishell *minishell)
{
	char	*input;
	char buf[2];

	ft_printf("> ");
	//
	buf[0] = ' ';
	buf[1] = '\0';
	input = ft_strdup("");
	while (buf[0] != '\n')
	{
		read(STDIN_FILENO, buf, 1);
		if (buf[0] != '\n')
			input = ft_strjoin(input, buf);
	}
}
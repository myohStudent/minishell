/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 10:27:27 by myoh              #+#    #+#             */
/*   Updated: 2020/12/03 16:46:05 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** 34 = single quote > 
** 39 = double quote <
** \' \" => > 프롬프트가 작동한다 -> 구현노노
** \\' \\" => > 프롬프트가 작동하지 않는다 -> 구현노노
** ' ', " " 안의 문자들은 스페이스나 기호가 있어도 파싱이나 스플릿하지 않고 모두 한 줄의 문자열로 간주한다 
*/

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
		if (s[i] == 34 && (i == 0)
			&& dquote % 2 == 0)
			quote++;
		if (s[i] == 39 && (i == 0 || dquote % 2 != 0)
			&& quote % 2 == 0)
			dquote++;
		i++;
	}
	if (quote % 2 != 0 || dquote % 2 != 0)
		return (1);
	return (0);
}

int		which_quote(char *input, t_minishell *minishell)
{
    int		quote;
	int		dquote;
	int		i;
    int     r;

    i = 0;
	r = 1;
	quote = 0;
	dquote = 0;
	while (input[i])
	{
		if (input[i] == 34 && (i == 0)) // '가 처음에 튀어나왔다
			minishell->quote[0]++; // '
		if (input[i] == 39 && (i == 0)) // "가 처음에 튀어나왔다
			minishell->quote[1]++; // ""
		i++;
	}
	if (minishell->quote[0] % 2 != 0 || minishell->quote[1] % 2 != 0)
		return (1);
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
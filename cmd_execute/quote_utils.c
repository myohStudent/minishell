///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   quote_utils.c                                      :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2020/11/26 10:27:27 by myoh              #+#    #+#             */
///*   Updated: 2020/12/06 17:45:16 by myoh             ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */

//#include "../minishell.h"

///*
//** 34 = single quote '
//** 39 = double quote "
//** \' \" => > 프롬프트가 작동한다 -> 구현노노
//** \\' \\" => > 프롬프트가 작동하지 않는다 -> 구현노노

//** ' ', " " 안의 문자들은 스페이스나 기호가 있어도 파싱이나 스플릿하지 않고 모두 한 줄의 문자열로 간주한다 
//** '가 들어오면 '가 나올 때 까지 반복문을 사용해서 ' ' 안에있는 부분을 다 명령어1로 저장
//** '가 끝나면 다음 명령어는 다음 노드에 저장.('dfxzgs'   'jhjh)


//hasquote이지만 스페이스가 없을 경우에는 통째로 명령어 처리합니다.
//옵션부분은 자동으로 들어가므로 '를 없애주는 처리만 하면 됩니다.
//** "하고 str[1]이 $이면 ENV와 strcmp해서 ==0인경우 ENV로 치환
//** ==0이 아니면 ENV로 치환하지않고 그대로 print
//*/

//int		in_quotes(char *s, int p)
//{
//	int	quote;
//	int	dquote;
//	int	i;

//	quote = 0;
//	dquote = 0;
//	i = 0;
//	while (i <= p)
//	{
//		if (s[i] == 34 && (i == 0) && dquote % 2 == 0)
//			quote++;
//		if (s[i] == 39 && (i == 0 || dquote % 2 != 0) && quote % 2 == 0)
//			dquote++;
//		i++;
//	}
//	if (quote % 2 != 0 || dquote % 2 != 0)
//		return (1);
//	return (0);
//}

//int		which_quote(char *input, t_minishell *minishell)
//{
//    int		quote;
//	int		dquote;
//	int		i;
//    int     r;

//    i = 0;
//	r = 1;
//	minishell->quote[0] = 0;
//	minishell->quote[1] = 0;
//	while (input[i])
//	{
//		if (input[i] == 34 && (i == 0)) // '가 처음에 튀어나왔다
//			minishell->quote[0]++; // '
//		if (input[i] == 39 && (i == 0)) // "가 처음에 튀어나왔다
//			minishell->quote[1]++; // ""
//		i++;
//	}
//	if (minishell->quote[0] % 2 != 0 || minishell->quote[1] % 2 != 0)
//		return (1);
//    return (0);
//}

//void	prompt_quote(t_minishell *minishell)
//{
//	char	*input;
//	char buf[2];

//	ft_printf("> ");
//	//
//	buf[0] = ' ';
//	buf[1] = '\0';
//	input = ft_strdup("");
//	while (buf[0] != '\n')
//	{
//		read(STDIN_FILENO, buf, 1);
//		if (buf[0] != '\n')
//			input = ft_strjoin(input, buf);
			

//	}
//}
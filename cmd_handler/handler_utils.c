/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 19:50:45 by myoh              #+#    #+#             */
/*   Updated: 2021/01/07 21:49:23 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		free_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

char		*parse_space(char *s, char *space)
{
	int		i;

	i = 0;
	if (!space || !s)
		return (NULL);
	while (ft_strchr(s, space && s[i] != '\0'))
	{
		s++;
		i++;
	}
	i = ft_strlen(s);
	while (ft_strchr(space, s[i]) && s != 0)
		i--;
	return (ft_substr(s, 0, i + 1));
}

int			exceptions2(char *input, int i)
{
	while (input[i])
	{
		if (input[i] == '|' && input[i + 1] == '|')
		{
			ft_printf("syntax error near unexpected token `|'\n");
			return (-1);
		}
		else if (input[i] == '<' && (input[i + 1] == '<' ||
			input[i + 1] == '>'))
		{
			ft_printf("syntax error near unexpected token `newline'\n");
			return (-1);
		}
		else if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
		{
			ft_printf("syntax error near unexpected token `newline'\n");
			return (-1);
		}
		i++;
	}
	return (1);
}

int			exceptions(char *input)
{
	int		i;

	i = 0;
	if (!input)
		return (-1);
	if (input[i] == '|')
	{
		ft_printf("syntax error near unexpected token `|'\n");
		return (-1);
	}
	else if (input[i] == '>' || input[i] == '<')
	{
		ft_printf("syntax error near unexpected token `newline'\n");
		return (-1);
	}
	if (exceptions2(input, i) < 0)
		return (-1);
	return (1);
}

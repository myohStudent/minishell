/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:53:45 by myoh              #+#    #+#             */
/*   Updated: 2020/12/29 00:06:28 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_char_here(char c, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int is_instr(char c, char *str)
{
	if (is_char_here(c, str) >= 0)
		return (1);
	return (0);
}

int has_pipes(char *option)
{
	int res;

	res = 0;
	if (!option)
		return (res);
	while (*option)
	{
		if (*option == '|')
			res++;
		option++;
	}
	ft_printf("pipe개수: %d\n", res);
	return (res);
}

int has_redirs(char *option)
{
	int res;

	res = 0;
	if (!option)
		return (res);
	while (*option)
	{
		if (ft_strchr("<>", *option))
			res++;
		option++;
	}
	ft_printf("redirs개수: %d\n", res);
	return (res);
}

int has_dollar(char *str)
{
	int res;

	res = 0;
	while (str[res])
	{
		if (str[res] == '$')
			return (res);
		res++;
	}
	ft_printf("$있는가: %d\n", res);

	return (0);
}

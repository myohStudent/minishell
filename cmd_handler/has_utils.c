/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:53:45 by myoh              #+#    #+#             */
/*   Updated: 2020/11/16 20:29:56 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			has_pipes(char *option)
{
	int		res;

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

int			has_redirs(char *option)
{
	int		res;

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

int		has_dollar(char *str)
{
	int	res;

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
int		has_quotes(char *option)
{
	int	res;

	res = 0;
	while (*option)
	{
		if (*option == '\'' || *option == '\"') // \', /"
			return (1);
	}
	ft_printf("quote있는가: %d\n", res);
	return (0);
}
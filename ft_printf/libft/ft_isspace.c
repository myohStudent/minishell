/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 15:52:41 by seohchoi          #+#    #+#             */
/*   Updated: 2020/11/15 14:59:26 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isspace(int c)
{
	if (c == ' ' || c == '\r' || c == '\t')
		return (1);
	return (0);
}

int		ft_ispipe(int c)
{
	if (c == '|')
		return (1);
	return (0);
}

int		ft_isbracket(int c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}
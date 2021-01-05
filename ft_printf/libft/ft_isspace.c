/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 15:52:41 by seohchoi          #+#    #+#             */
/*   Updated: 2021/01/05 22:15:29 by seohchoi         ###   ########.fr       */
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

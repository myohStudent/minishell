/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:55:39 by seohchoi          #+#    #+#             */
/*   Updated: 2020/04/19 09:42:52 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				ft_strchr(const char *s, int c)
{
	unsigned char	s2;
	int				i;

	s2 = (unsigned char)c;
	i = 0;
	while (s[i] != s2 && s && s[i])
		i++;
	if (s[i] == s2)
		return (s[i]);
	return (0);
}

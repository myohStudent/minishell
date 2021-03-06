/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:55:39 by seohchoi          #+#    #+#             */
/*   Updated: 2020/10/17 16:28:02 by myoh             ###   ########.fr       */
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

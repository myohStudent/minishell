/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:54:44 by seohchoi          #+#    #+#             */
/*   Updated: 2020/10/02 21:39:10 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*a;
	int		i;

	i = 0;
	if (!(a = (char *)malloc(sizeof(char) * (len))))
		return (NULL);
	while (i < (int)len)
	{
		a[i] = s[start];
		i++;
		start++;
	}
	a[i] = 0;
	return (a);
}

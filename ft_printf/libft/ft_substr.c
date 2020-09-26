/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:54:44 by seohchoi          #+#    #+#             */
/*   Updated: 2020/04/19 09:35:59 by seohchoi         ###   ########.fr       */
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

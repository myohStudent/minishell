/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 09:33:43 by seohchoi          #+#    #+#             */
/*   Updated: 2020/09/26 21:44:13 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_utoa(long long n)
{
	char			*answer;
	int				number;
	long long		dest;

	number = ft_numlen(n);
	dest = n;
	if (!(answer = (char *)malloc(sizeof(char) * (number))))
		return (NULL);
	answer[number] = 0;
	while (number-- > 0)
	{
		answer[number] = dest % 10 + '0';
		dest /= 10;
	}
	if (n == 0)
		answer[0] = '0';
	return (answer);
}
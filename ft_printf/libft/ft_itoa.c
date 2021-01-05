/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 09:35:40 by seohchoi          #+#    #+#             */
/*   Updated: 2021/01/05 22:15:24 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_numlen(long long n)
{
	int				number;

	number = 0;
	if (n == 0)
		number = 1;
	if (n < 0)
	{
		number = 1;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		number++;
	}
	return (number);
}

char				*ft_itoa(int n)
{
	char			*answer;
	int				number;
	int				neg_flag;
	long long		dest;

	neg_flag = (n >= 0) ? 1 : -1;
	dest = (n > 0) ? n : -n;
	if (n == -2147483648)
		dest = 2147483648;
	number = ft_numlen(n);
	if (!(answer = (char *)malloc(sizeof(char) * (number))))
		return (NULL);
	answer[number] = 0;
	while (number-- > 0)
	{
		answer[number] = dest % 10 + '0';
		dest /= 10;
	}
	if (neg_flag < 1)
		answer[0] = '-';
	if (n == 0)
		answer = ft_strdup("0");
	return (answer);
}

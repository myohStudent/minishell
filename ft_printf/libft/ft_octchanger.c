/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_octchanger.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 09:42:02 by seohchoi          #+#    #+#             */
/*   Updated: 2020/04/21 20:14:37 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long		ft_octnumlen(unsigned long num)
{
	int				len;

	len = 0;
	while (num)
	{
		num /= 8;
		len++;
	}
	return (len);
}

char				*ft_octchanger(unsigned long num)
{
	char			*oct;
	char			*result;
	int				len;
	int				i;

	oct = ft_strdup("01234567");
	len = ft_octnumlen(num);
	result = (char *)malloc(sizeof(char) * len + 1);
	if (num == 0)
	{
		result[0] = '0';
		result[1] = 0;
		free(oct);
		return (result);
	}
	i = len - 1;
	while (i >= 0)
	{
		result[i] = oct[num % 8];
		num /= 8;
		i--;
	}
	result[len] = 0;
	free(oct);
	return (result);
}

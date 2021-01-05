/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 15:56:24 by myoh              #+#    #+#             */
/*   Updated: 2021/01/05 22:15:15 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strlcat(char *dst, const char *src, int dstsize)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	if (dstsize)
	{
		while ((i + j) < (dstsize - 1) && src[j])
		{
			dst[i + j] = src[j];
			j++;
		}
		dst[i + j] = '\0';
	}
	while (src[j])
		j++;
	if (i < dstsize)
		return (i + j);
	return (dstsize + j);
}

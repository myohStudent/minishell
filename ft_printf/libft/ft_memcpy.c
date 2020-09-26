/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 20:46:38 by myoh              #+#    #+#             */
/*   Updated: 2020/04/10 18:21:10 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dst1;
	unsigned char	*src1;

	if (!dst || !src)
		return (0);
	i = 0;
	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	if (n == 0)
		return (dst);
	while (i < n)
	{
		dst1[i] = src1[i];
		i++;
	}
	return (dst);
}

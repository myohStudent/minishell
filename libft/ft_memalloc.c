/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 14:11:15 by myoh              #+#    #+#             */
/*   Updated: 2020/09/16 14:11:22 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*mem;
	char	*p;

	mem = (char*)malloc(size);
	if (mem == NULL)
		return (NULL);
	p = mem;
	while (size--)
		*p++ = 0;
	return (mem);
}
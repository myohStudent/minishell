/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 01:50:38 by seohchoi          #+#    #+#             */
/*   Updated: 2020/04/10 18:37:42 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_calloc(size_t count, size_t size)
{
	unsigned char	*a;
	size_t			len;

	len = count * size;
	if (!(a = malloc(len)))
		return (a);
	ft_bzero(a, len);
	return (a);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:58:50 by seohchoi          #+#    #+#             */
/*   Updated: 2020/08/13 17:26:34 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_bzero(void *ptr, size_t n)
{
	unsigned char	*ptr_temp;

	ptr_temp = (unsigned char *)ptr;
	while ((int)n-- > 0)
		*ptr_temp++ = 0;
}

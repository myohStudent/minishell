/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:14:27 by myoh              #+#    #+#             */
/*   Updated: 2020/02/27 18:16:36 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void       *ft_calloc(size_t count, size_t size)
{
    size_t              n;
    size_t              i;
    unsigned char       *buf;

    n = count * size;
    if (!(buf = (unsigned char *)malloc(n)))
        return (NULL);
    i = 0;
    while (i < n)
    {
            buf[i++] = 0;
    }
    return ((void *)buf);
}
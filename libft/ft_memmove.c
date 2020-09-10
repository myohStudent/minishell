/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:53:22 by myoh              #+#    #+#             */
/*   Updated: 2020/03/02 14:39:44 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    *ft_memmove(void *dst, const void *src, size_t len)
{
    unsigned char    *dst1;
    unsigned char    *src1;
    size_t  i;

    i = 0;
    dst1 = (unsigned char *)dst;
    src1 = (unsigned char *)src;
    if (len == 0)
        return (dst);
    if (!dst && !src)
        return (NULL);
    if (dst1 > src1)
    {
        while (len > 0)
        {
            len--;
            dst1[len] = src1[len];
        }
    }
    else
    {
        while (i < len)
            dst1[i++] = *(src1++);
    }
    return (dst);
}
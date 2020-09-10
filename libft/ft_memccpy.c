/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 13:51:06 by myoh              #+#    #+#             */
/*   Updated: 2020/03/02 11:15:17 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void        *ft_memccpy(void *dst, const void *src, int c, size_t n)
{
    char        *dst1;
    char        *src1;
    size_t      i;

    i = 0;
    dst1 = (char *)dst;
    src1 = (char *)src;

    if (n == 0)
        return (NULL);
    if (!dst1 && !src1)
        return (NULL);
    while (i < n)
    {
        dst1[i] = src1[i];
        if (dst1[i] == (unsigned char)c)
            return (dst1 + i + 1);
        i++;
    }
    return (NULL);
}
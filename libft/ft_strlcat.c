/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:20:34 by myoh              #+#    #+#             */
/*   Updated: 2020/02/26 09:48:58 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t          ft_strlcat(char *dst, const char *src, size_t dstsize)
{
    size_t      i;
    size_t      srcsize;
    size_t      dstsize_ori;

    i = 0;
    srcsize = 0;
    dstsize_ori = 0;
    while (src[srcsize])
        srcsize++;
    while (dst[dstsize_ori])
        dstsize_ori++;
    if (!dst && !src)
        return (0);
    if (dstsize == 0)
        return (srcsize);
    if (dstsize_ori >= dstsize)
        return (srcsize + dstsize);
    while (src[i] != '\0' && dstsize - 1 > i + dstsize_ori)
    {
        dst[i + dstsize_ori] = src[i];
        i++;
    }
    dst[i + dstsize_ori] = '\0';
    return (dstsize_ori + srcsize);
}
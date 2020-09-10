/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 09:13:57 by myoh              #+#    #+#             */
/*   Updated: 2020/03/02 13:57:32 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    *ft_memcpy(void *dst, const void *src, size_t n)
{
    size_t      i;
    char            *dst1;
    char            *src1;

    i = 0;
    dst1 = dst;
    src1 = (char *)src;
    if (n == 0)
        return (dst);
    while (i < n)
    {
        dst1[i] = src1[i];   
        i++;
    }
    return (dst);
}
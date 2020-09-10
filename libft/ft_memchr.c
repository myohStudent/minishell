/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:09:01 by myoh              #+#    #+#             */
/*   Updated: 2020/02/25 17:10:37 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memchr(const void *s, int c, size_t n)
{
    unsigned char       *str;
    size_t              i;

    i = 0;
    str = (unsigned char *)s;
    if (n == 0)
        return (NULL);
    while (i < n)
    {
        if (*(str + i) == (unsigned char)c)
            return (str + i);
        i++;
    }
    return (NULL);
}
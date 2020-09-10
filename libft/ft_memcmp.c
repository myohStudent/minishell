/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:21:15 by myoh              #+#    #+#             */
/*   Updated: 2020/03/02 15:04:29 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_memcmp(const void *s1, const void *s2, size_t n)
{
    unsigned char           *str1;
    unsigned char           *str2;
    size_t                  i;

    str1 = (unsigned char *)s1;
    str2 = (unsigned char *)s2;
    i = 0;
    if (!str1 || !str2)
        return (str1[i] - str2[i]);
    if (n == 0)
        return (0);
    while (i < n && str1[i] == str2[i])
        i++;
    if (n == i)
        return (0);
    return(str1[i] - str2[i]);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:00:13 by myoh              #+#    #+#             */
/*   Updated: 2020/03/02 15:43:15 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int         ft_strncmp(const char *s1, const char *s2, size_t n)
{
    int     i;

    i = 0;
    while(*s1 && *(s1 + i) == *(s2 + i) && i < (int)n - 1)
        i++;
	if (n != 0)
        return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
    return (0);
}
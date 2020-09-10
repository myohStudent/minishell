/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:24:44 by myoh              #+#    #+#             */
/*   Updated: 2020/02/25 00:23:38 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    *ft_memset(void *b, int c, size_t len)
{
    size_t          i;
    
    i = 0;
    while (i < len)
    {
        ((unsigned char *)b)[i] = c;
        i++;
    }
    return ((void *)b);
}
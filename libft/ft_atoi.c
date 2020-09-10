/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:47:43 by myoh              #+#    #+#             */
/*   Updated: 2020/02/24 23:11:06 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_atoi(const char *str)
{
    int     res;
    int     i;
    int     sign;

    i = 0;
    sign = 1;
    res = 0;
    while (str[i] == ' ' || str[i] == '\f' || str[i] == '\t'
            || str[i] == '\r' || str[i] == '\n' || str[i] == '\v')
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    while (str[i] && str[i] >= '0' && str[i] <= '9')
    {
        res *= 10;
        res += str[i] - '0'; 
        i++;
    }
    res = res * sign;
    return (res);
}
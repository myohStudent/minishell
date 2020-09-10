/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:38:18 by myoh              #+#    #+#             */
/*   Updated: 2020/03/02 11:16:30 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int     size_est(int n)
{
    int         i;

    i = 0; 
    if (n < 0)
        i++;
    if (n == 0)
        return (1);
    while (!((n / 10) == 0 && (n % 10) == 0))
    {
        n = n / 10;
        i++;
    }
    return (i);
}

char    *ft_itoa(int n)
{
    int         i;
    char        *new;

    if (n == -2147483648)
		return (ft_strdup("-2147483648"));
    i = size_est(n);
    if (!(new = (char *)malloc(sizeof(char) * (i + 1))))
        return (NULL);
    new[i] = '\0';
    i--;
    if (n == 0)
        new[0] = '0';
    while (n < 0)
    {
        new[0] = '-';
        n *= -1;
        new[i--] = (n % 10)  + '0';
        n = n / 10;
    }
    while (n > 0)
    {
        new[i--] = (n % 10) + '0';
        n = n / 10;
    }
    return (new);
}
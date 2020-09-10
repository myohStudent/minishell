/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 14:45:21 by myoh              #+#    #+#             */
/*   Updated: 2020/03/02 11:18:55 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char        *ft_strdup(const char *s1)
{
    int     i;
    char    *new;

    i = 0;
    while(s1[i])
        i++;
    new = (char *)malloc(sizeof(new) * (i + 1));
    if (!new)
    {
        free(new);
        return (NULL);
    }
    new[i] = '\0';
    while (i > 0)
    {
        new[i - 1] = s1[i - 1];
        i--;
    }
    return (new);
}
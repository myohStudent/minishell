/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:05:30 by myoh              #+#    #+#             */
/*   Updated: 2020/09/18 17:23:55 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int  imsi_len(char const *s)
{
    int         i;

    i = 0;
    while (s[i] != '\0')
        i++;
    return (i);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
    char    *new;
    int     i;

    i = 0;
    if (!(s1) || !(s2))
        return (NULL);
    if(!(new = malloc(sizeof(char)
            * (imsi_len(s1) + imsi_len(s2) + 1))))
        return (NULL);
    while (s1[i] != '\0')
    {
        new[i] = s1[i];
        i++;
    }
    i = 0;
    while (s2[i] != '\0')
    {
        new[imsi_len(s1) + i] = s2[i];
        i++;
    }
    new[imsi_len(s1) +i] = '\0';
    return (new);
}
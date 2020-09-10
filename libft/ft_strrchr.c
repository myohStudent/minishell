/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 10:56:43 by myoh              #+#    #+#             */
/*   Updated: 2020/03/06 10:54:31 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char        *ft_strrchr(const char *s, int c)
{
    size_t      len;

    len = ft_strlen(s);
    if ((char)c == '\0')
        return ((char *)(s + len));
    while (len--)
    {
        if(*(s + len) == (char)c)
            return ((char *)(s + len));
    }
    return (NULL);
}
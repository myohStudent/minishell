/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:45:01 by myoh              #+#    #+#             */
/*   Updated: 2020/02/26 16:58:21 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
    if (!(*needle))
        return ((char *)haystack);
    while (*needle && *(haystack) != 0 && len > 0)
    {
        while (*(char *)haystack == *(char *)needle && len > 0) 
        {
            if (*(char *)(needle + 1) == '\0')
            {
                while (*(char *)(--needle) != '\0')
                   haystack--;
                return ((char *)(haystack));
            }
            haystack++;
            needle++;
            len--;
        }
        haystack++;
        len--;  
        while (*(needle - 1))
            needle--;      
    }
    return (NULL);
}
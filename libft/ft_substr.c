/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:01:29 by myoh              #+#    #+#             */
/*   Updated: 2020/03/02 11:22:13 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int  im_slen(char const *s)
{
    unsigned int    i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    unsigned int    i;
    char    *sub;

    i = 0;
    if (start > im_slen(s) || !(s))
        return (NULL);
    if (len < start)
	{
		if (!(sub = (char *)malloc(sizeof(char) * 1)))
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
    if (!(sub = (char *)malloc((sizeof(char) * (len + 1)))))
        return (NULL);
    while (s[start] != '\0' && len != 0)
    {
        sub[i++] = s[start++];
        len--;
    }
    sub[i] = '\0';
    return (sub);
}
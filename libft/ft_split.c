/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 15:37:51 by myoh              #+#    #+#             */
/*   Updated: 2020/03/01 13:11:31 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int         fstrlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;

	i = 0;
	if (dst == 0 || src == 0)
		return (0);
	if (dstsize == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

static unsigned int      imsi_count(char const *s, char c)
{
    unsigned int         nb;
    unsigned int         i;

	i = 0;
	nb = 0;
    if (s[i] == '\0')
        return (0);
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb++;
	return (nb);
}

static void             count_words(char **str, unsigned int *wordcount, char c)
{
    unsigned int        i;
    
    *str += *wordcount;
	*wordcount = 0;
	i = 0;
	while (**str && **str == c)
		(*str)++;
	while ((*str)[i])
	{
		if ((*str)[i] == c)
			return ;
		(*wordcount)++;
		i++;
	}
}

char                    **ft_split(char const *s, char c)
{
    unsigned int        i;
    unsigned int        cnt;
    unsigned int        wordcount;
    char                **new;
    char                *str;

    i = 0;
    if (!s)
        return (NULL);
    cnt = imsi_count(s, c);
    if (!(new = malloc(sizeof(char *) * (cnt + 1))))
        return (NULL);
    str = (char *)s;
    wordcount  = 0;
    while (i < cnt)
    {
        count_words(&str, &wordcount, c);
        if (!(new[i] = malloc(sizeof(char) * (wordcount + 1))))
        {
            free(new);
			return (NULL);
        }
		fstrlcpy(new[i], str, wordcount + 1);
		i++;
	}
	new[i] = NULL;
	return (new);
}
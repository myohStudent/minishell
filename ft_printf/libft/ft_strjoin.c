/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:31:54 by seohchoi          #+#    #+#             */
/*   Updated: 2021/01/05 22:13:10 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int			ft_strcat(char *dest, char const *src)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = 0;
	return (i + j);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		resultlen;

	i = 0;
	resultlen = (ft_strlen(s1) + ft_strlen(s2));
	if (!(result = (char *)malloc(sizeof(char) * (resultlen + 1))))
		return (NULL);
	*result = 0;
	while (i < resultlen)
	{
		i += ft_strcat(result, s1);
		if (i < resultlen)
			i += ft_strcat(result, s2);
	}
	result[resultlen] = 0;
	return (result);
}

char		*ft_strjoin_free(char *s1, char const *s2)
{
	int		size;
	int		i;
	int		j;
	char	*dst;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	if ((dst = ft_calloc(sizeof(char), size)) == NULL)
		return (NULL);
	i = -1;
	while (*(s1 + ++i))
		*(dst + i) = *(s1 + i);
	j = -1;
	while (*(s2 + ++j))
		*(dst + i + j) = *(s2 + j);
	*(dst + i + j) = '\0';
	free((char*)s1);
	return (dst);
}

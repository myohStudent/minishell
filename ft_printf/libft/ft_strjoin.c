/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:31:54 by seohchoi          #+#    #+#             */
/*   Updated: 2020/11/29 15:37:13 by myoh             ###   ########.fr       */
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

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*str;

	if (!s2)
	{
		str = ft_strdup(s1);
		free((void*)s1);
		return (str);
	}
	if (!(str = (char*)ft_calloc(1, sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	ft_strcat(str, s1); //strcpy
	free((void*)s1);
	ft_strcat(str, s2);
	free((void*)s2);
	return (str);
}
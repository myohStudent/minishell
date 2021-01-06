/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 11:17:23 by myoh              #+#    #+#             */
/*   Updated: 2021/01/06 11:22:35 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (!dst || !src)
		return (0);
	if (size > 0)
	{
		while (--size && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

char				**ft_free(char **s)
{
	int				i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	s = NULL;
	return (NULL);
}

int					ft_get_nb_strs(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_strs++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_strs++;
	return (nb_strs);
}

static void			ft_get_next_s(char **next_s, unsigned int *next_s_len,
					char c)
{
	unsigned int i;

	*next_s += *next_s_len;
	*next_s_len = 0;
	i = 0;
	while (**next_s && **next_s == c)
		(*next_s)++;
	while ((*next_s)[i])
	{
		if ((*next_s)[i] == c)
			return ;
		(*next_s_len)++;
		i++;
	}
}

char				**ft_split(char const *s, char c)
{
	char			**res;
	char			*next_s;
	unsigned int	next_s_len;
	unsigned int	nb_strs;
	unsigned int	i;

	if (!s)
		return (NULL);
	nb_strs = ft_get_nb_strs(s, c);
	if (!(res = (char **)malloc(sizeof(char *) * (nb_strs + 1))))
		return (NULL);
	i = 0;
	next_s = (char *)s;
	next_s_len = 0;
	while (i < nb_strs)
	{
		ft_get_next_s(&next_s, &next_s_len, c);
		if (!(res[i] = (char *)malloc(sizeof(char) * (next_s_len + 1))))
			return (ft_free(res));
		ft_strlcpy(res[i], next_s, next_s_len + 1);
		i++;
	}
	res[i] = NULL;
	return (res);
}

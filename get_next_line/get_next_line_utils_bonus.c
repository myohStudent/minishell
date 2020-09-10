/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 20:22:42 by myoh              #+#    #+#             */
/*   Updated: 2020/05/22 14:57:00 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t					ft_strlen(const char *s)
{
	size_t				i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char					*ft_strdup(char *s)
{
	size_t				i;
	char				*new;

	i = 0;
	if (!(new = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	while (s[i] != '\0')
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char					*ft_strjoin(char *s1, char *s2)
{
	char				*new;
	unsigned int		i;
	unsigned int		j;
	unsigned int		s1_len;
	unsigned int		s2_len;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1 || !s2)
		return (!s1 ? ft_strdup(s2) : ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(new = (char *)malloc(sizeof(char) *
					(s1_len + s2_len + 1))))
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = -1;
	free(s1);
	while (s2[++j])
		new[i++] = s2[j];
	new[i] = '\0';
	return (new);
}

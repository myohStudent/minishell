/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 20:22:42 by myoh              #+#    #+#             */
/*   Updated: 2020/09/13 19:58:56 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char					*j_strjoin(char *s1, char *s2)
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

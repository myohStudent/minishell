/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 21:41:52 by myoh              #+#    #+#             */
/*   Updated: 2021/01/05 22:14:57 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	int			size;

	if (!set || !s1)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1 != '\0')
		s1++;
	size = ft_strlen((char *)s1);
	while (ft_strchr(set, s1[size]) && size != 0)
		size--;
	return (ft_substr((char *)s1, 0, size + 1));
}

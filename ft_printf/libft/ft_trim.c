/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:02:52 by myoh              #+#    #+#             */
/*   Updated: 2021/01/07 17:10:20 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_del(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

char		*ft_trim(char *s)
{
	char	*a;
	int		i;
	int		j;
	int		l;

	if (!s)
		return (NULL);
	i = 0;
	while (ft_del(s[i]) == 1)
		i++;
	j = ft_strlen(s) - 1;
	while (ft_del(s[j]) == 1)
		j--;
	l = j - i + 1;
	if (l < 0)
		return (ft_strdup(""));
	a = (char *)malloc(sizeof(char) * l + 1);
	if (a == NULL)
		return (NULL);
	j = 0;
	while (j < l)
		a[j++] = s[i++];
	a[j] = '\0';
	return (a);
}

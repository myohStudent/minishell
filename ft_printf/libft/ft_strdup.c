/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 19:53:22 by seohchoi          #+#    #+#             */
/*   Updated: 2020/04/21 20:40:33 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*a;
	int		i;

	i = 0;
	if (!src)
		return (a = ft_strdup("(null)"));
	while (src[i])
		i++;
	i++;
	a = (char *)malloc(sizeof(char) * (i));
	i = 0;
	while (src[i])
	{
		a[i] = src[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

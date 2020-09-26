/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 09:42:13 by seohchoi          #+#    #+#             */
/*   Updated: 2020/04/19 09:42:14 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdchar(char src)
{
	char	*a;
	int		i;

	i = 1;
	a = (char *)malloc(sizeof(char) * (i + 1));
	*a = 0;
	a[0] = src;
	a[1] = '\0';
	return (a);
}

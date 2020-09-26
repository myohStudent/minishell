/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 09:42:09 by seohchoi          #+#    #+#             */
/*   Updated: 2020/04/19 20:35:40 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int		ft_putstr(char *s, char type, char character)
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		write(1, s, 1);
		s++;
		i++;
	}
	if (type == 'c' && character == '\0' && !*s)
	{
		write(1, s++, 1);
		i++;
		while (*s)
		{
			write(1, s++, 1);
			i++;
		}
	}
	return (i);
}

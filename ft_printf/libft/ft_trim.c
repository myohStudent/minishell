/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:02:52 by myoh              #+#    #+#             */
/*   Updated: 2021/01/05 22:12:07 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*trim_before(char *s)
{
	if (s)
	{
		while (*s == '\t' || *s == ' ')
			s++;
	}
	return (s);
}

int			trim_end(char *s)
{
	int		end;

	end = ft_strlen(s);
	end--;
	if (s)
	{
		while (s[end] == '\t' || s[end] == ' ')
			end--;
	}
	return (end + 1);
}

char		*ft_trim(char *s)
{
	char	*res;
	char	*trimmed;
	int		len_trimmed;
	int		i;

	if (!s)
		return (NULL);
	s = trim_before(s);
	len_trimmed = trim_end(s);
	if ((trimmed = (char *)malloc(sizeof(char) * (len_trimmed + 1))) == NULL)
		return (NULL);
	res = trimmed;
	i = 0;
	while (i < len_trimmed)
	{
		if (!ft_isspace(s[i]))
			*trimmed++ = s[i];
		else if ((i - 1 >= 0) && (!ft_isspace(s[i - 1])))
			(s[i] == '\t') ? (*trimmed++ = ' ') : (*trimmed++ = s[i]);
		i++;
	}
	*trimmed = '\0';
	return (res);
}

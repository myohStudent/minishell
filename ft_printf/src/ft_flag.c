/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 09:04:23 by seohchoi          #+#    #+#             */
/*   Updated: 2020/04/23 20:19:53 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_width_flag(int contentlen, int index, char *src)
{
	char	*result;
	int		i;

	i = -1;
	result = (char *)malloc(sizeof(char) * (contentlen + 1));
	if (t_flag.hyphen != 1)
	{
		while (i++ < index)
			result[i] = ' ';
		i = 0;
		while (index < contentlen && src[i])
		{
			result[index] = src[i];
			index++;
			i++;
		}
		if (!*src && t_flag.type == 'c' && t_flag.character == '\0')
			result[index - 1] = src[0];
		result[index] = 0;
	}
	else
		result = ft_hyphen_flag(contentlen, result, src);
	return (result);
}

char		*ft_pre_flag(int contentlen, int index, char *src)
{
	char	*result;
	int		i;

	i = -1;
	result = (char *)malloc(sizeof(char) * (contentlen + 1));
	if (t_flag.pre > t_flag.conlen)
	{
		while (i++ < index)
			result[i] = '0';
		i = 0;
		while (index < contentlen && src[i])
		{
			result[index] = src[i];
			index++;
			i++;
		}
		result[index] = 0;
	}
	else if (!(t_flag.pre) && src[0] == '0')
		result[0] = 0;
	else
		result = ft_strdup(src);
	free(src);
	return (result);
}

char		*ft_zero_flag(char *src)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = ft_strdup(src);
	while (src[i] && t_flag.minus && !(ft_strchr("+-", src[i])))
		i++;
	if (t_flag.ishash && t_flag.ispre == 0 && !t_flag.hyphen)
		result = ft_hashwithzero_flag(result, src);
	else if (t_flag.ispre == 0 || j < (t_flag.pre - t_flag.conlen) ||
	t_flag.type == '%')
	{
		if (ft_strchr("+-", src[i]))
			result[j++] = src[i];
		if (t_flag.minus == 2)
			j++;
		while (result[j] == '-' || result[j] == ' ' || result[j] == '+')
		{
			result[j] = '0';
			j++;
		}
	}
	return (result);
}

char		*ft_ox_hash_flag(char *result, char type)
{
	char	*str;
	int		i;

	i = 0;
	t_flag.ishash = 1;
	if (type == 'x' || type == 'p' || type == 'P')
		str = ft_strdup("0x");
	if (type == 'X')
		str = ft_strdup("0X");
	if (type != 'p')
		if (t_flag.unumber != 0)
		{
			str = ft_strjoin(str, result);
			return (str);
		}
	if (type == 'p')
	{
		if (!(t_flag.ispre && !t_flag.pre && *result == '0'))
			str = ft_strjoin(str, result);
		return (str);
	}
	t_flag.ishash = 0;
	return (result);
}

char		*ft_neg_flag(char *result)
{
	char	dest[2];
	char	*str;

	if (t_flag.minus == 1)
		dest[0] = '-';
	if (t_flag.minus == 2)
		dest[0] = ' ';
	else if (t_flag.minus == 3)
		dest[0] = '+';
	dest[1] = 0;
	str = ft_strjoin(dest, result);
	free(result);
	return (str);
}

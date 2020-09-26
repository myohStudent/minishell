/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 09:21:19 by seohchoi          #+#    #+#             */
/*   Updated: 2020/04/23 02:51:19 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_initialize(void)
{
	t_flag.hyphen = 0;
	t_flag.zero = 0;
	t_flag.minus = 0;
	t_flag.width = 0;
	t_flag.conlen = 0;
	t_flag.pre = 0;
	t_flag.type = 0;
	t_flag.ispre = 0;
	t_flag.character = 0;
	t_flag.number = 0;
	t_flag.unumber = 0;
	t_flag.ulong = 0;
	t_flag.ishash = 0;
}

char		*ft_spe_checker(char type, va_list ptr)
{
	char	*result;

	result = NULL;
	ft_arg_getter(type, ptr);
	if (type == 'd' || type == 'i' || type == 'D' || type == 'I')
		result = ft_itoa(t_flag.number);
	else if (type == 'u' || type == 'U')
		result = ft_utoa(t_flag.unumber);
	else if (type == 's' || type == 'S')
		result = ft_strdup(va_arg(ptr, char *));
	else if (type == 'x')
		result = ft_strtolower(ft_hexchanger(t_flag.unumber));
	else if (type == 'X')
		result = ft_hexchanger(t_flag.unumber);
	else if (type == 'o' || type == 'O')
		result = ft_octchanger(t_flag.unumber);
	else if (type == 'c' || type == 'C')
		result = ft_strdchar(t_flag.character);
	else if (type == 'p' || type == 'P')
		result = ft_strtolower(ft_hexchanger(t_flag.ulong));
	else if (type == '%')
		result = ft_strdup("%");
	return (result);
}

void		ft_flag_checker(const char *input, va_list ptr, char type)
{
	char	*result;

	ft_getter(input, ptr);
	result = ft_spe_checker(type, ptr);
	result = ft_neg_checker(result, input, type);
	t_flag.conlen = ft_strlen(result);
	if ((type == 's') && (t_flag.conlen > t_flag.pre) && t_flag.ispre)
		result = ft_substr(result, 0, t_flag.pre);
	else if ((ft_strchr("dDioOuUxX", type)) && t_flag.ispre)
		result = ft_pre_flag(t_flag.conlen + (t_flag.pre - t_flag.conlen),\
		(t_flag.pre - t_flag.conlen), result);
	if ((ft_strchr(input, '#') && (ft_strchr("oOxX", type))) || type == 'p')
		result = ft_ox_hash_flag(result, type);
	if (t_flag.minus)
		result = ft_neg_flag(result);
	t_flag.conlen = ft_strlen(result);
	if (t_flag.width && (t_flag.width - t_flag.conlen) > 0)
		result = ft_width_flag(t_flag.width, \
		(t_flag.width - t_flag.conlen), result);
	if (t_flag.width && t_flag.zero == 1 && (ft_strchr("dDioOuUxXsS%", type)))
		result = ft_zero_flag(result);
	t_flag.relen += ft_putstr(result, t_flag.type, t_flag.character);
	free(result);
}

char		*ft_neg_checker(char *result, const char *input, char type)
{
	if (*input == '#')
		input++;
	t_flag.hyphen = ft_flagchr(input, "-");
	if (ft_strchr("dDiI", type))
	{
		if (*input == ' ' && *result != '-')
			t_flag.minus = 2;
		else if (*input == '+' && *result != '-')
			t_flag.minus = 3;
		else if (*result == '-')
		{
			result = (ft_strdup(result + 1));
			t_flag.minus = 1;
		}
		if (t_flag.minus > 1 && *input != ' ')
			input++;
	}
	t_flag.zero = ft_flagchr(input, "0");
	return (result);
}

int			ft_flagchr(const char *input, char *flag)
{
	while (ft_strchr("#0- +", *input))
	{
		if (ft_strchr(flag, *input))
			return (1);
		input++;
	}
	if (*flag == '-')
		return (t_flag.hyphen);
	else
		return (t_flag.zero);
}

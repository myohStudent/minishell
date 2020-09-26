/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 09:04:19 by seohchoi          #+#    #+#             */
/*   Updated: 2020/04/23 02:59:47 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_getter(const char *input, va_list ptr)
{
	t_flag.width = ft_width_getter(input, ptr);
	ft_precision_getter(input, ptr, t_flag.type);
}

char		ft_type_getter(const char *input)
{
	char	type;

	while (ft_strchr("#0-+' ", *input) || \
	ft_strchr("$*.", *input) || ft_isdigit(*input))
		input++;
	if ((type = ft_strchr("dDioOuUxXeEfFgGaAcCsSpn%", *input)))
		return (type);
	return (0);
}

void		ft_arg_getter(char type, va_list ptr)
{
	if (ft_strchr("dDiI", type))
		t_flag.number = va_arg(ptr, int);
	else if (ft_strchr("xXuUoO", type))
		t_flag.unumber = va_arg(ptr, unsigned int);
	else if (ft_strchr("pP", type))
		t_flag.ulong = va_arg(ptr, unsigned long);
	else if (ft_strchr("cC", type))
		t_flag.character = va_arg(ptr, int);
}

int			ft_width_getter(const char *input, va_list ptr)
{
	int		width;

	width = 0;
	while (ft_strchr("#0-+' ", *input))
		input++;
	if (*input == '*')
	{
		width = va_arg(ptr, int);
		if (width < 0)
		{
			width *= -1;
			t_flag.hyphen = 1;
		}
	}
	else
		while (ft_isdigit(*input))
		{
			width *= 10;
			width += (*input) - '0';
			input++;
		}
	return (width);
}

void		ft_precision_getter(const char *input, va_list ptr, char type)
{
	while (*input != type && *input != '.' && *input)
		input++;
	if (*input == '.')
	{
		t_flag.ispre = 1;
		input++;
	}
	if (*input == '*')
	{
		t_flag.pre = va_arg(ptr, int);
		if (t_flag.pre < 0)
		{
			t_flag.ispre = 0;
			t_flag.pre *= -1;
		}
	}
	else
		while (ft_isdigit(*input))
		{
			t_flag.pre *= 10;
			t_flag.pre += (*input) - '0';
			input++;
		}
}

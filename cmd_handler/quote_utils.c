/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 21:30:46 by myoh              #+#    #+#             */
/*   Updated: 2021/01/04 01:22:04 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_isquote(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

int			get_first_quote(char *command, int type)
{
	int		i;

	i = 0;
	if (type != 1 && type != 2)
		return (-1);
	while (command[i])
	{
		if (ft_isquote(command[i]) == type)
			return (i);
		i++;
	}
	return (-1);
}

int			has_quotes(t_cmd *new)
{
	int		isdouble;
	int		isquote;
	int		i;

	isdouble = 0;
	isquote = 0;
	i = 0;
	while (new->command[i])
	{
		if (new->quote_type != 2)
			if (ft_isquote(new->command[i]) == 1)
				isquote++;
		if (new->quote_type != 1)
			if (ft_isquote(new->command[i]) == 2)
				isdouble++;
		i++;
		if (isquote == 2 || isdouble == 2)
			return (i);
	}
	return (0);
}

void		check_quote_type(int isdouble, int isquote, t_cmd *new)
{
	if (isdouble == 2 && ((get_first_quote(new->command, 1) <
	get_first_quote(new->command, 2)) || !get_first_quote(new->command, 1)))
		new->hasenv = 1;
	if (isdouble == 2 &&
	get_first_quote(new->command, 1) > -1 &&
	get_first_quote(new->command, 1) <
	get_first_quote(new->command, 2))
		new->quote_type = 1;
	if (isquote == 2 &&
	get_first_quote(new->command, 2) > -1 &&
	get_first_quote(new->command, 1) > get_first_quote(new->command, 2))
	{
		new->quote_type = 2;
		new->hasenv = 1;
	}
}

int			get_quote_type(t_cmd *new)
{
	int		isdouble;
	int		isquote;
	int		i;

	isdouble = 0;
	isquote = 0;
	i = 0;
	while (new->command[i])
	{
		if (ft_isquote(new->command[i]) == 1)
			isquote++;
		if (ft_isquote(new->command[i]) == 2)
			isdouble++;
		i++;
		check_quote_type(isdouble, isquote, new);
		if (isquote == 2 || isdouble == 2)
		{
			new->hasquote = 1;
			return (i);
		}
	}
	new->hasquote = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:53:45 by myoh              #+#    #+#             */
/*   Updated: 2020/10/24 00:11:29 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			has_pipes(char *option)
{
	int		res;

	res = 0;
	while (*option)
	{
		if (*option == '|')
		{
			res++;
		}
		option++;
	}
	ft_printf("pipe개수: %d\n", res);
	return (res);
}
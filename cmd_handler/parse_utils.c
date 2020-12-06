/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:48:33 by myoh              #+#    #+#             */
/*   Updated: 2020/12/06 20:53:10 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_trimchar(char *str, char c)
{
	int i;
	int currindex;
	char *res; 

	i = 0;
	currindex = 0;
	while (str[i])
	{
		if (str[i] != c)
			currindex++;
		i++;
	}
	res = (char *)malloc(sizeof(char) * (currindex + 1));
	i = 0;
	currindex = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			res[currindex] = str[i];
			currindex++;
		}
		i++;
	}
	res[currindex] = '\0';
	return (res);
}
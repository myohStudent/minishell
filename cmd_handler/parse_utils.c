/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:48:33 by myoh              #+#    #+#             */
/*   Updated: 2020/12/14 20:40:48 by myoh             ###   ########.fr       */
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

char		*space_trim(char *s)
{
	int		len;
	char	*t;
	char	*end;
	char	*begin;

	begin = ft_strdup(s);
    while (*begin != '\0')
    {
        if (ft_isspace(*begin))
          	begin++;
        else
        {  
          s = ft_strdup(begin);
          break;
        }  
    }
	t = ft_strdup(s);
	len = ft_strlen(s);
	end = t + len - 1;
	while (end != t && ft_isspace(*end))
        end--;
    *(end + 1) = '\0';
    s = ft_strdup(t);
    return (s);
}
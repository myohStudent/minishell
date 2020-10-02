/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 19:50:45 by myoh              #+#    #+#             */
/*   Updated: 2020/10/02 22:03:21 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int        env_index(t_minishell *minishell, char *str)
{
    int     i;
    int     l;

    l = ft_strlen(str);
    i = 0;
    while (minishell->env_set[i] && minishell->env_set[i + 1])
	{
		if (ft_strncmp(minishell->env_set[i], str, l) == 0)
     		return (i + 1);
    }
    return (-1);
}
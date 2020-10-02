/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 23:12:29 by myoh              #+#    #+#             */
/*   Updated: 2020/10/02 17:56:04 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    cmd_export(t_cmd *curr, t_minishell *minishell)
{
    int i;
    i = 0;
    // use ft_strjoin
    if (curr->argc == 1)
    {
        while (minishell->env_temp[i] != NULL)
	    {
		    ft_printf("%s=%s\n", minishell->env_temp[i], minishell->env_temp[i+1]);
		    i++;
	    	i++;
	    }
	    ft_printf("\n");
    }
    //if (curr->argc == 2)
}
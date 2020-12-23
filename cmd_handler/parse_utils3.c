/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 11:04:26 by myoh              #+#    #+#             */
/*   Updated: 2020/12/23 11:46:52 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			get_cmd_argc(t_cmd *new)
{
    ft_printf("new->type:/%d/ opt:/%s/\n", new->type, new->option);
	if (ft_compare(new->command, "cd"))
	{
		if (new->type > 3)
		{
			if (new->option = NULL)
				new->argc = 1;
			new->argc = 2;
		}
	}
	if (ft_compare(new->command, "export"))
	{
		if (new->type == LASTPIPE)
		{
			if (ft_compare(new->option, ""))
			 	new->argc = 1; 
			else
				new->argc = 42;
		}
		else if (new->type > 3)
		{
            if (ft_compare(new->option, ""))
                new->argc = 2;
            else
                new->argc = 1;
		}
    }
    if (ft_compare(new->command, "unset"))
    {
        if (new->type == LASTPIPE)
            new->argc = 42;
        else if (new->type > 3)
            new->argc = 2;
    }
}
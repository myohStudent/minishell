/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 21:51:14 by myoh              #+#    #+#             */
/*   Updated: 2020/12/06 21:55:35 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void        cmd_echo(t_cmd *curr, t_minishell *minishell)
{
    if (curr->option && ft_strncmp(curr->option, "-n", 2) == 0)
			ft_putstr_fd(curr->option + 3, 1);
		if (curr->option && ft_strncmp(curr->option, "$?\0", 3) == 0)
		{
			ft_printf("%d\n", g_command_nb);
			g_command_nb = 0;
		}
		else
		{
			if (curr->option)
			{
                ft_putstr_fd(curr->option, 1);
            	g_command_nb = 0;
            }
			ft_putchar('\n');
		}
}
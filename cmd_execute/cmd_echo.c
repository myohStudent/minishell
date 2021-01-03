/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 21:51:14 by myoh              #+#    #+#             */
/*   Updated: 2021/01/03 15:22:07 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		cmd_echo(t_cmd *curr, t_minishell *minishell)
{
	if (curr->option && ft_strncmp(curr->option, "-n", 2) == 0)
	{
		if (!curr->option[2])
		{
			ft_printf("");
			g_command_nb = 0;
			return ;
		}
		else if (curr->option[2] != ' ')
			ft_printf("%s", curr->option);
		else
			ft_printf("%s", curr->option + 3);
	}
	else if (curr->option && ft_strncmp(curr->option, "$?\0", 3) == 0)
		ft_printf("%d", g_command_nb);
	else
	{
		if (curr->option)
			ft_putstr_fd(curr->option, 1);
	}
	g_command_nb = 0;
	ft_putchar('\n');
}

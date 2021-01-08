/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 18:17:11 by myoh              #+#    #+#             */
/*   Updated: 2021/01/08 22:30:56 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		cmd_cd(t_cmd *curr, t_minishell *minishell)
{
	if (curr->argc == 1)
	{
		if (chdir(g_home_dir) < 0)
		{
			g_command_nb = 0;
			return (-1);
		}
		g_command_nb = 0;
	}
	else if (curr->argc == 2)
	{
		if (curr->argc >= 2)
		{
			if (chdir(curr->option) < 0)
			{
				ft_printf("cd: %s\n", strerror(errno));
				g_command_nb = 1;
			}
		}
	}
	return (1);
}

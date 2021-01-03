/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 18:17:11 by myoh              #+#    #+#             */
/*   Updated: 2021/01/03 16:16:54 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		cmd_cd(t_cmd *curr, t_minishell *minishell)
{
	if (curr->argc == 1)
	{
		if (chdir(g_home_dir) < 0)
		{
			g_command_nb = 127;
			return (-1);
		}
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

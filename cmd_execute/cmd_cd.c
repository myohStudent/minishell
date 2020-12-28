/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 18:17:11 by myoh              #+#    #+#             */
/*   Updated: 2020/12/28 23:41:02 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		cmd_cd(t_cmd *curr, t_minishell *minishell)
{
	ft_printf("cd opt:%s, argc:%d\n",curr->option, curr->argc);
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
			if (chdir(curr->option) < 0) //경로가 실제 존재하는지 체크합니다.
			{
				ft_printf("cd: %s\n", strerror(errno));
				g_command_nb = 1;
			}
		}
	}
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 18:17:11 by myoh              #+#    #+#             */
/*   Updated: 2020/12/06 21:55:07 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		cmd_cd(t_cmd *curr, t_minishell *minishell)
{
	if (curr->argc == 1)
	{
		if (chdir(home_dir) < 0)
		{
			g_command_nb = 127;
			return (-1);
		}
	}
	else if (curr->option)
	{
		if (curr->argc == 2)
		{
			if (chdir(curr->option) < 0) //경로가 실제 존재하는지 체크합니다.
			{
				ft_printf("cd: %s\n", strerror(errno));
				g_command_nb = 1;
			}
		}
		else if (curr->argc > 2)
		{	
			ft_putstr_fd("cd: too many arguments\n", 1);
			g_command_nb = 127;
		}
	}
	return (1);
}
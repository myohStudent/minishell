/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:14:53 by myoh              #+#    #+#             */
/*   Updated: 2020/12/06 21:53:38 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		cmd_exit(t_cmd *curr, t_minishell *minishell)
{
	if (curr->argc == 1 || curr->argc == 2)
	{	ft_putstr_fd("\n[Process Completed]\0", 1);
		g_command_nb = 1;
		exit(1);
	}
	else
	{
		ft_putstr_fd("\nexit: too many arguments\0", 1);
		ft_putstr_fd("\n", 1);
		g_command_nb = 127;
		return (-1);
	}

}
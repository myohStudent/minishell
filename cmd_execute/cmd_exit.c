/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:14:53 by myoh              #+#    #+#             */
/*   Updated: 2021/01/03 15:25:14 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		exit_clear(t_cmd *curr, t_minishell *minishell)
{
	clear_scmd(curr, minishell);
	exit(1);
}

void		digit_exit(t_cmd *curr, t_minishell *minishell)
{
	int		i;

	i = 0;
	while (curr->option[i])
	{
		if (!(ft_isdigit(curr->option[i])))
		{
			ft_printf("%s: $s: a numeric argument required\n",
			curr->command, curr->option);
			exit_clear(curr, minishell);
		}
		i++;
	}
}

void		cmd_exit(t_cmd *curr, t_minishell *minishell)
{
	int		i;

	i = 0;
	if (curr->argc == 1 || curr->argc == 2)
	{
		g_command_nb = 1;
		if (curr->option)
			digit_exit(curr, minishell);
		ft_putstr_fd("\nexit\n", 1);
		exit_clear(curr, minishell);
	}
	else if (curr->argc == 0)
		;
	else
	{
		ft_putstr_fd("\nexit: too many arguments\0", 1);
		ft_putstr_fd("\n", 1);
		g_command_nb = 255;
		exit_clear(curr, minishell);
	}
}

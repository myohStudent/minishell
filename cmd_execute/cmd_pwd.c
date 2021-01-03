/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:59:08 by myoh              #+#    #+#             */
/*   Updated: 2021/01/03 15:37:12 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_pwd(t_cmd *curr, t_minishell *minishell)
{
	ft_putstr_fd(getcwd(minishell->path, 4096), 1);
	g_command_nb = 0;
	ft_putchar('\n');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:59:08 by myoh              #+#    #+#             */
/*   Updated: 2020/12/19 16:29:40 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_pwd(t_cmd *curr, t_minishell *minishell)
{
	ft_putstr_fd(getcwd(minishell->path, 4096), 1);
	g_command_nb = 0;
	ft_putchar('\n');
}
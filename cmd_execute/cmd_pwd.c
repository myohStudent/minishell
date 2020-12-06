/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:59:08 by myoh              #+#    #+#             */
/*   Updated: 2020/12/06 17:59:40 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_pwd(t_cmd *curr, t_minishell *minishell)
{
	ft_putstr_fd(getcwd(minishell->path, 4096), 1);
	g_command_nb = 0;
	// if (curr->argc == 1 || curr->option == NULL)
	// {
	// 	ft_putstr_fd(getcwd(minishell->path, 4096), 1);
	// 	g_command_nb = 0;
	// }
	// // else if (curr->argc > 1 && curr->option)
	// // {
	// // 	ft_putstr_fd("pwd: too many arguments", 1);
	// // 	g_command_nb = 127;
	// // }
	// else if (curr->argc > 1)
	// {
	// 	ft_putstr_fd(getcwd(minishell->path, 4096), 1);
	// 	g_command_nb = 0;
	// }
	ft_putchar('\n');
}
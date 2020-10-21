/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:48:58 by myoh              #+#    #+#             */
/*   Updated: 2020/10/21 23:10:13 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_env(t_minishell *minishell)
{
	int		i;
	int		j;

	i = 0;
	j = arr_len(minishell->env_set);
	if (minishell->export_set[0] != NULL)
	{
		while (minishell->export_set[i] != NULL && i < minishell->env_nb)
		{
			ft_printf("%s\n", minishell->env_set[i]);
			i++;
		}
		while (minishell->export_set[i] != NULL)
		{
			ft_printf("%s\n", minishell->export_set[i]);
			i++;
		}
	}
	else
	{
		while (minishell->env_set[i])
		{
			ft_printf("%s\n", minishell->env_set[i]);
			i++;
		}
	}
	ft_printf("\n");
}
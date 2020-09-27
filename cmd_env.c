/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:48:58 by myoh              #+#    #+#             */
/*   Updated: 2020/09/27 21:47:45 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	cmd_env(t_minishell *minishell)
{
	int		i;
	//int		j;
	i = 3;
	while (minishell->env_temp[i] != NULL)
	{
		if (i == 3)
			ft_printf("%s=%s\n", minishell->env_temp[0], minishell->env_temp[1]);
		if (i / 2 != 0)
		{
			ft_printf("%s", minishell->env_temp[i]);
			if (minishell->env_temp[i + 1] != NULL)
				ft_printf("=%s\n", minishell->env_temp[i + 1]);
		}
		i++;
	}
	ft_printf("\n");
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:48:58 by myoh              #+#    #+#             */
/*   Updated: 2020/10/02 15:26:09 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	cmd_env(t_minishell *minishell)
{
	int		i;
	//int		j;
	i = 0;
	while (minishell->env_temp[i] != NULL)
	{
		ft_printf("%s=%s\n", minishell->env_temp[i], minishell->env_temp[i+1]);
		i++;
		i++;
	}
	ft_printf("\n");
}
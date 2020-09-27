/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:48:58 by myoh              #+#    #+#             */
/*   Updated: 2020/09/27 20:48:09 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	cmd_env(t_minishell *minishell)
{
	int		i;
	int		j;

	i = 0;
	while (minishell->env_temp[i])
	{
		j = 0;
		if (!(i / 2))
		{
			while (minishell->env_temp[i][j] != '\0' && minishell->env_temp[i + 1] != NULL)
			{
				write(1, &minishell->env_temp[i][j], 1);
				j++;
			}
			if ((minishell->env_temp[i + 1]))
				write(1, "=", 1);
		}
		else
		{
			while (minishell->env_temp[i][j] != '\0')
			{
				write(1, &minishell->env_temp[i][j], 1);
				j++;
			}
		}
		write(1, "\n", 1);
		i++;
	}
}
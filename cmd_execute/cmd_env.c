/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:48:58 by myoh              #+#    #+#             */
/*   Updated: 2020/10/17 15:57:54 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_env(t_minishell *minishell)
{
	int		i;
	int		j;

	i = 0;
	j = arr_len(minishell->env_set);
	while (i < minishell->env_nb && minishell->env_set[i+1] != NULL)
	{
		ft_printf("%s=%s\n", minishell->env_set[i], minishell->env_set[i+1]);
		i++;
		i++;
	}
	if (minishell->env_currnb != 0)
	{
		while (i < minishell->env_currnb)
		{
			ft_printf("%s=%s\n", minishell->env_set[i], minishell->env_set[i+1]);
			i++;
			i++;
		}
	}
	/*while (minishell->env_set[i] != NULL && i < j - 1)
	{
		ft_printf("%s=%s\n", minishell->env_set[i], minishell->env_set[i+1]);
		i++;
		i++;
	}*/
	ft_printf("\n");
}
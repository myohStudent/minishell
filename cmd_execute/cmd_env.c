/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:48:58 by myoh              #+#    #+#             */
/*   Updated: 2020/10/18 13:21:24 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_env(t_minishell *minishell)
{
	int		i;
	int		j;

	i = 0;
	j = arr_len(minishell->env_set);
	/*if (minishell->export_set[0] != NULL)
	{
		while (minishell->export_set[i] != NULL)
		{
			ft_printf("%s\n", minishell->export_set[i]);
			i++;
		}
	}
	else*/
	{
		while (minishell->env_set[i])
		{
			ft_printf("%s\n", minishell->env_set[i]);
			i++;
		}
	}
	/*while (i < minishell->env_nb && minishell->env_set[i+1] != NULL)
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
	}*/
	/*while (minishell->env_set[i] != NULL && i < j - 1)
	{
		ft_printf("%s=%s\n", minishell->env_set[i], minishell->env_set[i+1]);
		i++;
		i++;
	}*/
	ft_printf("\n");
}
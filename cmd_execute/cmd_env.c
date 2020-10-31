/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:48:58 by myoh              #+#    #+#             */
/*   Updated: 2020/10/31 23:30:43 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_env(t_minishell *minishell)
{
	int		i;
	int		j;

	i = -1;
	j = arr_len(minishell->env_set);
	ft_printf("들어왔냐! ");
	if (minishell->export_set != NULL) //얘가 에러가 나네
	{
		ft_printf("넵! ");

		while (++i < minishell->env_nb && minishell->export_set[i] != NULL)
			ft_printf("%s\n", minishell->env_set[i]);
		while (minishell->export_set[i] != NULL)
		{
			ft_printf("%s\n", minishell->export_set[i]);
			i++;
		}
	}
	else
	{
		ft_printf("헉! ");
		while (minishell->env_set[++i])
			ft_printf("%s\n", minishell->env_set[i]);
	}
	ft_printf("\n");
}
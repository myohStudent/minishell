/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:48:58 by myoh              #+#    #+#             */
/*   Updated: 2020/11/01 15:39:28 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_env(t_minishell *minishell)
{
	int	i;
	t_list *lst;
	//t_env *env;

	if (!minishell->env_list)
		return ;
	i = 0;
	lst = minishell->env_list; //start 시작점 포인터로 넘기기
	while (lst)
	{
		// + export용 인덱스 필요함
		if (lst->content && ((t_env *)(lst->content))->variable != NULL)	
		{
			ft_printf("%s=%s\n", ((t_env *)(lst->content))->variable,
				((t_env *)(lst->content))->value);
		}
		lst = lst->next;
	}
}
/*
void	cmd_env(t_minishell *minishell)
{
	int		i;
	int		j;

	i = -1;
	j = arr_len(minishell->env_set);
	if (minishell->export_set != NULL) //얘가 [0]로 하면 에러가 났었네
	{

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
		while (minishell->env_set[++i])
			ft_printf("%s\n", minishell->env_set[i]);
	}
	ft_printf("\n");
}*/
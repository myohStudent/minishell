/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 22:55:01 by myoh              #+#    #+#             */
/*   Updated: 2020/10/21 23:00:58 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**arr_unset(t_cmd *curr, t_minishell *minishell)
{
	char	**res;
	int		i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (arr_len(minishell->export_set)));
	while (minishell->export_set[i] != NULL)
	{
		if (ft_strcmp(minishell->export_set[i], curr->option))
			res[i] = ft_strdup(minishell->export_set[i]);
		else
			i++;
		i++;
	}
	ft_printf("(%d)",i);
	res[i] = ft_strdup(minishell->export_set[i]);
	res[i + 1] = NULL;
	ft_printf("(%d)\n", i);
	free_arr(minishell->export_set);
	minishell->env_currnb = i + 1; // 넘버 추가
	return (res);
}

void	cmd_unset(t_cmd *curr, t_minishell *minishell)
{
	int	i;
	int j;
	char **str;

	i = 0;
	j = 0;
	if (curr->argc == 1) //한 개일 때 출력
		ft_printf("unset: not enough arguments\n");
	if (curr->argc >= 2 && curr->option != NULL)			
	{
		if (!(str = ft_split(curr->option, ' ')))
			return ;
		while (str[i])
		{
			if (ft_strchr(str[i], '=') != 0)
			{
				ft_printf("unset: %s: invalid parameter name\n",str[i]);
				i++;
				continue ;
			}
			while (minishell->export_set[i] != NULL && i < minishell->env_currnb)
			{
				if (ft_strncmp(minishell->export_set[i], curr->option, j + 1) == 0)
				{

				}
			i++;
			}
		}
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 22:55:01 by myoh              #+#    #+#             */
/*   Updated: 2020/10/24 21:20:29 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	multi_options(t_cmd *curr)
{
	int	i;
	int	j;
	int	nb;
	int	l;

	nb = 0;
	i = 0;
	j = 0;
	l = 0;
	if (curr->option)
	{
		while (curr->option[i] && curr->option[i] != '|')
		{
			if (ft_isspace(curr->option[i]))
				nb++;
			i++;
		}
		i = 0;
		ft_printf("nb: %d ", nb);
		if (nb == 0)
			return ;
		if (!(curr->option_av = (char **)malloc(sizeof(char *) * (nb + 1))))
			return ;
		while (curr->option[i] && i < nb && curr->option[i] != '|')
		{
			if (!ft_isspace(curr->option[i]))
				curr->option_av[j][l] = curr->option[i];
			if (ft_isspace(curr->option[i]))
			{
				j++;
				l = -1;
			}
			i++;
			l++;
		}
	}
	i = 0;
	while (curr->option_av[i])
	{
		ft_printf("%s ", curr->option_av[i]);
		i++;
	}
	ft_printf("\n");
}

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
		multi_options(curr); // option 인자가 여러 개면 이중배열에다 순서대로 집어넣기
		/*if (!(str = ft_split(curr->option, ' ')))
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
		}*/
	}
}
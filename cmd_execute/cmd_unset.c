/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 22:55:01 by myoh              #+#    #+#             */
/*   Updated: 2021/01/03 17:02:39 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_envremove(t_env *list, char **remove, t_minishell *minishell)
{
	t_env	*prev;
	int		i;

	i = 0;
	prev = NULL;
	while (list && i < minishell->env_currnb)
	{
		if (ft_strcmp(list->variable, remove[0]) == 0)
		{
			if (prev != NULL)
				prev->next = list->next;
			else if (prev == NULL)
				minishell->export_list = list->next;
			free(list->variable);
			if (list->value)
				free(list->value);
		}
		prev = list;
		list = list->next;
	}
}

void		cmd_unset(t_cmd *curr, t_minishell *minishell)
{
	char	**remove_env;
	char	**split_remove_env;
	int		i;

	i = 0;
	if (curr->argc <= 1)
		return ;
	if (curr->argc > 1 && curr->argc != 42)
	{
		remove_env = ft_split(curr->option, ' ');
		while (remove_env[i] != NULL)
		{
			split_remove_env = ft_split(remove_env[i], '=');
			ft_envremove(minishell->export_list, split_remove_env, minishell);
			ft_envremove(minishell->env_list, split_remove_env, minishell);
			minishell->env_currnb--;
			i++;
			free_arr(split_remove_env);
		}
		free_arr(remove_env);
	}
	g_command_nb = 0;
}

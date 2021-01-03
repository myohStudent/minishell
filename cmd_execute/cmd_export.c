/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 11:06:43 by myoh              #+#    #+#             */
/*   Updated: 2021/01/03 17:01:08 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			sort_env(t_minishell *minishell)
{
	int			i;
	int			j;
	t_env		*prev_node;
	t_env		*curr_node;
	t_env		*next_node;

	i = minishell->env_currnb;
	while (i)
	{
		j = 0;
		curr_node = minishell->export_list;
		prev_node = NULL;
		while (j < i && curr_node->next)
		{
			if (ft_strcmp(curr_node->variable, curr_node->next->variable) > 0)
			{
				next_node = curr_node;
				curr_node = curr_node->next;
				next_node->next = curr_node->next;
				curr_node->next = next_node;
				if (prev_node != NULL)
					prev_node->next = curr_node;
				else if (prev_node == NULL)
					minishell->export_list = curr_node;
			}
			prev_node = curr_node;
			curr_node = curr_node->next;
			j++;
		}
		i--;
	}
}

void			envadd_back(t_env *list, char **newenv, t_minishell *minishell)
{
	t_env		*new_node;
	int			i;

	i = 0;
	new_node = (t_env *)malloc(sizeof(t_env));
	new_node->variable = ft_strdup(newenv[0]);
	if (newenv[1])
		new_node->value = ft_strdup(newenv[1]);
	else
		new_node->value = NULL;
	while (list->next && i < minishell->env_currnb)
	{
		list = list->next;
		i++;
	}
	new_node->next = NULL;
	list->next = new_node;
}

int				ft_cmp_to_update(t_env *list, char **split_new_env, t_minishell *minishell)
{
	int			i;

	i = 0;
	while (list && i < minishell->env_currnb)
	{
		i++;
		if (ft_strcmp(list->variable, split_new_env[0]) == 0)
		{
			if (list->value)
				free(list->value);
			list->value = ft_strdup(split_new_env[1]);
			return (1);
		}
		list = list->next;
	}
	return (0);
}

int				ft_update_env(t_minishell *minishell, char **split_new_env)
{
	t_env		*env;
	t_env		*export;

	env = minishell->env_list;
	export = minishell->export_list;
	if (ft_cmp_to_update(env, split_new_env, minishell) == 1)
	{
		ft_cmp_to_update(export, split_new_env, minishell);
		return (1);
	}
	return (0);
}

void			cmd_export(t_cmd *curr, t_minishell *minishell)
{
	char		**new_env;
	char		**split_new_env;
	int			i;

	i = 0;
	if (!minishell->export_list)
	{
		minishell->export_list = (t_env *)malloc(sizeof(t_env));
		copy_env(minishell, minishell->export_list, minishell->env_list);
	}
	sort_env(minishell);
	if (curr->argc == 1)
		print_export(minishell->export_list);
	if (curr->argc > 1 && curr->argc != 42)
	{
		new_env = ft_split(curr->option, ' ');
		while (new_env[i] != NULL)
		{
			ft_printf("\n[%s]\n", new_env[i]);
			split_new_env = ft_split(new_env[i], '=');
			if (ft_update_env(minishell, split_new_env) == 0)
			{
				envadd_back(minishell->export_list, split_new_env, minishell);
				envadd_back(minishell->env_list, split_new_env, minishell);
				minishell->env_currnb++;
			}
			i++;
			free_arr(split_new_env);
		}
		free_arr(new_env);
	}
}

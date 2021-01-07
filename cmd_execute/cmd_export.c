/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 11:06:43 by myoh              #+#    #+#             */
/*   Updated: 2021/01/08 04:14:41 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			sort_env_one(t_minishell *minishell, int i)
{
	t_env		*prev_node;
	t_env		*curr_node;
	t_env		*next_node;
	int			j;

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
}

void			sort_env(t_minishell *minishell)
{
	int			i;
	int			j;

	i = minishell->env_currnb;
	while (i)
	{
		sort_env_one(minishell, i);
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

int				ft_cmp_to_update(t_env *list, char **split_new_env,
				t_minishell *minishell)
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

void			cmd_export(t_cmd *curr, t_minishell *minishell)
{
	char		**new_env;
	int			i;

	i = 0;
	sort_env(minishell);
	if (curr->argc == 1)
		print_export(minishell->export_list);
	if (curr->argc > 1 && curr->argc != 42)
	{
		new_env = ft_split(curr->option, ' ');
		while (new_env[i] != NULL)
		{
			add_new_env(minishell, new_env[i]);
			i++;
		}
		free_arr(new_env);
	}
}

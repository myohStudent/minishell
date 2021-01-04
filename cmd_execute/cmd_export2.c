/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 15:31:15 by myoh              #+#    #+#             */
/*   Updated: 2021/01/04 01:56:21 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void			copy_env(t_minishell *minishell, t_env *export_list, t_env *env)
{
	if (env == NULL)
		return ;
	minishell->env_currnb = 0;
	while (env)
	{
		export_list->variable = ft_strdup(env->variable);
		export_list->value = ft_strdup(env->value);
		minishell->env_currnb++;
		if (env->next)
		{
			export_list->next = (t_env *)malloc(sizeof(t_env));
			export_list = export_list->next;
		}
		env = env->next;
	}
	export_list->next = NULL;
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

void			add_new_env(t_minishell *minishell, char *new_env)
{
	char		**split_new_env;

	split_new_env = ft_split(new_env, '=');
	if (ft_update_env(minishell, split_new_env) == 0)
	{
		envadd_back(minishell->export_list, split_new_env, minishell);
		envadd_back(minishell->env_list, split_new_env, minishell);
		minishell->env_currnb++;
	}
	free_arr(split_new_env);
}

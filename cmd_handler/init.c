/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 21:25:44 by myoh              #+#    #+#             */
/*   Updated: 2021/01/08 03:39:00 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			init_env(char **env, t_minishell *minishell, t_env *env_list)
{
	int			i;
	char		**str;

	i = 0;
	minishell->env_currnb = 0;
	g_sigexit = 0;
	while (env[i])
	{
		str = ft_split(env[i], '=');
		if (ft_strncmp(str[0], "HOME\0", 5) == 0)
			g_home_dir = ft_strdup(str[1]);
		env_list->variable = ft_strdup(str[0]);
		env_list->value = ft_strdup(str[1]);
		if (env[i + 1])
		{
			env_list->next = (t_env *)malloc(sizeof(t_env));
			env_list = env_list->next;
		}
		free_arr(str);
		minishell->env_currnb++;
		i++;
	}
	env_list->next = NULL;
	minishell->export_list = (t_env *)malloc(sizeof(t_env));
	copy_env(minishell, minishell->export_list, minishell->env_list);
}

void			get_envp(char **env, int i)
{
	int			j;

	j = 0;
	g_envp_list = (char **)malloc(sizeof(char *) * i);
	while (j < i)
	{
		g_envp_list[j] = ft_strdup(env[j]);
		j++;
	}
	g_envp_list[j] = NULL;
}

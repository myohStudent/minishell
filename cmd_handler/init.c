/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 21:25:44 by myoh              #+#    #+#             */
/*   Updated: 2021/01/03 17:06:19 by myoh             ###   ########.fr       */
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
}
char            **get_binfromtemp(char *temp)
{
    char        **bin;

    if (temp)
	{
		bin = ft_split(temp, ':');
		free(temp);
		temp = NULL;
	}
    return (bin);
}

void			get_path(t_env *list, t_minishell *minishell)
{
	char		**bin;
	char		*temp;
	int			i;
	t_env		*l;

	l = list;
	i = -1;
	while (l && ++i < minishell->env_currnb)
	{
		if (ft_strcmp(l->variable, "PATH") == 0)
		{
			temp = ft_strdup(l->value);
			break ;
		}
		l = l->next;
	}
    bin = get_binfromtemp(temp);
	i = 0;
	while (bin[i])
		i++;
	g_pipe_bin = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (bin && bin[++i])
		g_pipe_bin[i] = ft_strjoin(bin[i], "/");
    free_arr(bin);
}

void			get_envp(char **env, int i)
{
	int		 	j;

	j = 0;
	g_envp_list = (char **)malloc(sizeof(char *) * i);
	while (j < i)
	{
		g_envp_list[j] = ft_strdup(env[j]);
		j++;
	}
	g_envp_list[j] = NULL;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 14:38:30 by myoh              #+#    #+#             */
/*   Updated: 2020/10/11 14:39:25 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_unsetenv(char **env, char *variable)
{
	int index;

	if (!variable || *env == NULL)
		return (0);
	index = getindex(*env, variable);
	if (index != -1)
		*env = remove_env(*env, index);
	return (1);
}

static int		getindex(char **env, char *variable)
{
	int index;
	int cntr;

	index = 0;
	cntr = 0;
	if (env == NULL)
		ft_printf("No environment :\n"); 
	while (env[index] != NULL)
	{
		while (env[index][cntr] && variable[cntr] && env[index][cntr] == variable[cntr])
		{
			if (env[index][cntr + 1] == '=')
				return (index);
			cntr++;
		}
		index++;
	}
	return (-1);
}

static char		**remove_env(char **env, int index)
{
	char	**cpy;
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (env[i] != NULL)
		i++;
	cpy = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i] != NULL)
	{
		if (i != index)
			cpy[i - cnt] = ft_strdup(env[i]);
		else
			cnt++;
	}
	ft_strdel(env);
	cpy[i - cnt] = NULL;
	return (cpy);
}
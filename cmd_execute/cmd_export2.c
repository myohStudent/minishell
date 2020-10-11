/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 14:35:25 by myoh              #+#    #+#             */
/*   Updated: 2020/10/11 14:38:07 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_copy(char **env)  
{
	char	**cpy;
	size_t	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	cpy = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i] != NULL)
		cpy[i] = ft_strdup(env[i]);
	cpy[i] = NULL;
	return (cpy);
}

char		*get_env(char **env, const char *variable)
{
	int i;
	int cntr;

	i = 0;
	if (env == NULL)
	{
		ft_printf("No Environment\n");
		return (NULL);
	}
	if (variable == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		cntr = 0;
		while (env[i][cntr] && variable[cntr] && env[i][cntr] == variable[cntr])
		{
			if (env[i][cntr + 1] == '\0')
			return ft_strdup("tes");
			if (env[i][cntr + 1] == '=')
				return (ft_strdup(ft_strchr(env[i] + cntr, '=') + 1));
			cntr++;
		}
		i++;
	}
		ft_putendl("---");
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:55:01 by myoh              #+#    #+#             */
/*   Updated: 2020/09/26 22:56:17 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*void	ft_exit(void)
{
	write(1, "\n", 1);
	exit(1);
}*/

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

static int	arr_len(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

char	**arr_realloc(char **arr, char *line)
{
	char	**res;
	int		i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (arr_len(arr) + 2));
	while (arr[i] != NULL)
	{
		res[i] = ft_strdup(arr[i]);
		i++;
	}
	res[i++] = ft_strdup(line);
	res[i] = NULL;
	i = 0;
	free_arr(arr);
	return (res);
}

char	**set_env(char **env)
{
	int		i;
	int		j;
	char	**new;
	char	*temp;

	i = arr_len(env);
	if (!(new = (char **)ft_memalloc(sizeof(char *) * (i + 1))))
		exit(1);
	new[0] = NULL;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		env[i][j] = '\0';
		temp = ft_strdup(env[i]);
		new = arr_realloc(new, temp);
		free(temp);
		temp = ft_strdup(&env[i][++j]);
		new = arr_realloc(new, temp);
		free(temp);
	}
	return (new);
}

void init_env(char **env, t_minishell *minishell)
{
	minishell->env->temp = set_env(env);
	ft_printf("%s\n", minishell->env->temp);
}
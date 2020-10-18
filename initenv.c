/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:55:01 by myoh              #+#    #+#             */
/*   Updated: 2020/10/18 13:18:56 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*void	ft_exit(void)
{
	write(1, "\n", 1);
	exit(1);
}*/

int		ft_before_chr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i + 1);
		i++;
	}
	return (0);		
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

int	arr_len(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
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
		if (!(new[i] = ft_strdup(env[i])))
			exit(1);
		i++;
	}
	/*while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		env[i][j] = '\0';
		temp = ft_strdup(env[i]);
		new = arr_realloc(new, temp);
		free(temp);
		j++;
		temp = ft_strdup(&env[i][j]);
		new = arr_realloc(new, temp);
		free(temp);
		i++;
	}*/
	return (new);
}

void init_env(char **env, t_minishell *minishell)
{
	int i;

	i = 0;
	minishell->env_set = set_env(env);
	minishell->env_nb = arr_len(minishell->env_set);
	minishell->env_currnb = minishell->env_nb;
	cpy_env(minishell, minishell->env_nb);
}

int		count_mots(char *str)
{
	int count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (ISSPACE(str[i]))
			i++;
		if (!ISSPACE(str[i]) && str[i] != '\0')
			count++;
		while (!ISSPACE(str[i]) && str[i] != '\0')
			i++;
	}
	return (count);
}
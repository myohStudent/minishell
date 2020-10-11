/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:55:01 by myoh              #+#    #+#             */
/*   Updated: 2020/10/11 15:12:59 by myoh             ###   ########.fr       */
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

int	arr_len(char **env)
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
		j++;
		temp = ft_strdup(&env[i][j]);
		new = arr_realloc(new, temp);
		free(temp);
		i++;
	}
	i = 0;
	return (new);
}

void init_env(char **env, t_minishell *minishell)
{
	int i = 0;
	minishell->env_set = set_env(env);
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

int		get_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (ISSPACE(str[i]))
		i++;
	while (!ISSPACE(str[i]) && str[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

char			**all_split(char *ss)
{
	int		i;
	int		j;
	int		k;
	char	**str2;

    i = -1;
    j = 0;
	if (!ss || !(str2 = (char **)malloc(sizeof(*str2) *
		(count_mots(ss) + 1))))
		return (NULL);
	while (++i < count_mots(ss))
	{
		k = 0;
		if (!(str2[i] = ft_strnew(get_len(&ss[j]) + 1)))
			str2[i] = NULL;
		while (IS_SPACE(ss[j]))
			j++;
		while (!IS_SPACE(ss[j]) && ss[j])
			str2[i][k++] = ss[j++];
		str2[i][k] = '\0';
	}
	str2[i] = 0;
	return (str2);
}
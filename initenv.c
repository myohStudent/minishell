/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:55:01 by myoh              #+#    #+#             */
/*   Updated: 2020/09/19 17:41:43 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./minishell.h"

void	ft_exit(char **environ)
{
	//free(environ);
	write(1, "\n", 1);
	exit(0);
}

static int		arr_len(char **env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
	{
		j++;
		i++;
	}
	return (j);
}

void init_env(char **env, t_minishell *minishell)
{
	int		i;
	char	**new;

	i = arr_len(env);
	printf("ㅇㅅㅇinit_env들어옴\n");
	minishell->env.temp = getenv(env);
	new = (char **)ft_memalloc(sizeof(char *) * (i + 1));
	i = 0;
	while (new[i])
	{
		if (!(new[i] = ft_strdup(env[i])))
			ft_exit(new[i]);
		i++;
	}
	minishell->env.temp = new;
	free(new);
	printf("ㅇㅅㅇinit_env나감\n");
}

/*char		*ft_get_env(const char *key)
{
	extern char		**environ;
	char			*return_str;
	int				i;
	int				j;
	int				k;
	i = -1;
	j = 0;
	k = 0;
	return_str = NULL;
	while (*(environ + ++i))
		if (ft_strnstr(*(environ + i), key, ft_strlen((char *)key)))
			break ;
	return (ft_exec_get_env(*(environ + i), key, j, k));
}*/
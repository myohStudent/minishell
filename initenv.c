/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 14:55:01 by myoh              #+#    #+#             */
/*   Updated: 2020/09/18 16:30:26 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./minishell.h"
/*
void	*ft_memalloc(size_t size)
{
	char	*mem;
	char	*p;

	mem = (char*)malloc(size);
	if (mem == NULL)
		return (NULL);
	p = mem;
	while (size--)
		*p++ = 0;
	return (mem);
}
*/
void	ft_exit(char **environ)
{
	//free(environ);
	write(1, "\n", 1);
	exit(0);
}/*

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

	i = arr_len(env);
	minishell->env.envp = (char **)ft_memalloc(sizeof(char *) * (i + 1));

	i = 0;
	while (minishell->env.envp[i])
	{
		if (!(minishell->env.envp[i] = ft_strdup(env[i])))
			ft_exit(minishell->env.envp);
		i++;
	}
}*/

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:48:58 by myoh              #+#    #+#             */
/*   Updated: 2020/11/21 20:37:18 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	print_env(t_env *env)
{
	int	i;
	//t_env *env;

	if (env == NULL)
		return (-1);
	while (env)
	{
		if (env->variable && env->value)
			ft_printf("declare -x %s=%s\n",env->variable,env->value);
		env = env->next;
	}
	return (1);
}

int	print_export(t_env *env)
{
	int	i;
	//t_env *env;

	if (env == NULL)
		return (-1);
	while (env)
	{
		if (env->variable && env->value)
			ft_printf("declare -x %s=%s\n",env->variable,env->value);
		env = env->next;
	}
	return (1);
}
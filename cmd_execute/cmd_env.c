/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:48:58 by myoh              #+#    #+#             */
/*   Updated: 2020/11/22 20:58:48 by seohchoi         ###   ########.fr       */
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
			ft_printf("%s=%s\n",env->variable,env->value);
		env = env->next;
	}
	return (1);
}

int	print_export(t_env *env)
{
	int	i = 1;
	//t_env *env;

	if (env == NULL)
		return (-1);
	while (env)
	{
		if (env->variable)
		{
			ft_printf("declare -x %s",env->variable);
			if (env->value)
				ft_printf("=\"%s\"",env->value);
			ft_printf("\n");
		}
		env = env->next;
	}
	return (1);
}
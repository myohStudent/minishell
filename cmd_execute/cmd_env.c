/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:48:58 by myoh              #+#    #+#             */
/*   Updated: 2021/01/03 15:23:11 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		print_env(t_env *env)
{
	int	i;

	if (env == NULL)
		return (-1);
	while (env)
	{
		if (env->variable && env->value)
			ft_printf("%s=%s\n", env->variable, env->value);
		env = env->next;
	}
	g_command_nb = 0;
	return (1);
}

int		print_export(t_env *env)
{
	int	i;

	i = 1;
	if (env == NULL)
		return (-1);
	while (env)
	{
		if (env->variable)
		{
			ft_printf("declare -x %s", env->variable);
			if (env->value)
				ft_printf("=\"%s\"", env->value);
			ft_printf("\n");
		}
		env = env->next;
	}
	return (1);
}

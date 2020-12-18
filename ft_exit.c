/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 19:07:13 by myoh              #+#    #+#             */
/*   Updated: 2020/12/16 18:17:56 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_exit()
{
	exit(1);
}

void	clear_env(t_env *env)
{
	if (env && env->variable != NULL)
	{
		free(env->variable);
		free(env->value);
		env = env->next;
	}
}
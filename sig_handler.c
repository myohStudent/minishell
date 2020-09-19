/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 15:52:51 by myoh              #+#    #+#             */
/*   Updated: 2020/09/19 17:05:54 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "minishell.h"

void ctrlc_handler(int signo)
{
	(void)signo;

	printf("\b\b \b\b");
	printf("\n");
	display_prompt();
}

void ctrld_handler(int signo)
{
	(void)signo;
	printf("\b\b \b\b");
}
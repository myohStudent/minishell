/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:11:24 by myoh              #+#    #+#             */
/*   Updated: 2021/01/05 22:18:36 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **upc, t_list *new)
{
	t_list	*imsi;

	if (!upc || !new)
		return ;
	if (*upc)
	{
		imsi = *upc;
		while (imsi->next)
			imsi = imsi->next;
		imsi->next = new;
	}
	else
	{
		*upc = new;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:57:34 by myoh              #+#    #+#             */
/*   Updated: 2021/01/05 22:20:20 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int	i;
	t_list	*imsi;

	i = 0;
	imsi = lst;
	while (imsi)
	{
		imsi = imsi->next;
		i++;
	}
	return (i);
}

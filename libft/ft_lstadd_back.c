/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 10:34:25 by myoh              #+#    #+#             */
/*   Updated: 2020/03/03 11:15:49 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list  *temp;

    if (!*lst)
    {
        *lst = new;
        return ;
    }
    temp = *lst;
    while (temp->next)
            temp = temp->next;
    if (new)
    {
        temp->next = new;
        new->next = NULL;
    }
}
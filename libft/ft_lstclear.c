/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 10:34:53 by myoh              #+#    #+#             */
/*   Updated: 2020/03/03 14:39:02 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_lstclear(t_list **lst, void (*del)(void *))
{
    t_list      *imsi;
    t_list      *entry;

    entry = *lst;
    while (entry)
    {
        imsi = entry->next;
        if (del)
            del(entry->content);
        free(entry);
        entry = imsi;
    }
    *lst = NULL;
}
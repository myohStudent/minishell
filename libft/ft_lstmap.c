/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 11:32:17 by myoh              #+#    #+#             */
/*   Updated: 2020/03/03 14:46:01 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list      *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list  *new;
    t_list  *first;

    if (!lst || !f || !del)
        return (NULL);
    if (!(new = ft_lstnew(f(lst->content))))
        return (NULL);
    first = new;
    while(lst)
    {
        if (lst->next)
        {
            if (!(new->next = ft_lstnew(f(lst->next->content))))
            {
                ft_lstclear(&first, del);
                return (NULL);
            }
            new = new->next;
        }
        lst = lst->next;
    }
    new->next = NULL;
    return (first);
}


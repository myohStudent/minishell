/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:35:03 by myoh              #+#    #+#             */
/*   Updated: 2020/03/03 09:41:46 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

t_list      *ft_lstnew(void *content)
{
    t_list          *new;

    new = (t_list *)malloc(sizeof(t_list));
    if (!new)
        return (NULL);
    if (content == NULL)
        new->content = NULL;
    if (content)
    {
        new->content = malloc(sizeof(content));
        if (!new->content)
        {
            free(new);
            return (NULL);
        }
        new->content = content;
    }
    new->next = NULL;
    return (new);
}
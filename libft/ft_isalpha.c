/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:52:19 by myoh              #+#    #+#             */
/*   Updated: 2020/02/27 11:30:33 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_isalpha(int c)
{
    if (((unsigned char)c >= 'A' && (unsigned char)c <= 'Z') ||
            ((unsigned char)c >= 'a' && (unsigned char)c <= 'z'))
        return ((unsigned char)c);
    return (0);
}

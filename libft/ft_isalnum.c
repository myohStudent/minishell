/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:44:18 by myoh              #+#    #+#             */
/*   Updated: 2020/02/27 11:51:12 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_isalnum(int c)
{
    return (((unsigned char)c >= '0' && (unsigned char)c <= '9')
            || ((unsigned char)c >= 'a' && (unsigned char)c <= 'z')
            || ((unsigned char)c >= 'A' && (unsigned char)c <= 'Z')
            ? 1 : 0);
}

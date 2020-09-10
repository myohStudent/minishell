/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 11:51:52 by myoh              #+#    #+#             */
/*   Updated: 2020/02/27 12:04:17 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int     ft_isascii(int c)
{
    return (((unsigned char)c >= 0 && (unsigned char)c <= 127)
            ? 1 : 0);
}
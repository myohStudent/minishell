/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 09:51:07 by myoh              #+#    #+#             */
/*   Updated: 2020/03/06 10:23:55 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char            *ft_strchr(const char *s, int c)
{
   if ((char)c == '\0')
      return ((char *)s + ft_strlen(s)); 
   if (!*s)
      return (NULL);
   while (*s)
   {
      if (*s == (char)c)
         return ((char *)s);
      s++;
   }
   return (NULL);
}
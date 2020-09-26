/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 09:32:57 by seohchoi          #+#    #+#             */
/*   Updated: 2020/09/26 22:52:20 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

char			*ft_utoa(long long n);
int				ft_tolower(int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtolower(char *str);
size_t			ft_strlen(const char *str);
int				ft_strcat(char *dest, char const *src);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *src);
char			*ft_strdchar(char src);
char			ft_strchr(const char *s, int c);
unsigned int	ft_putstr(char *s, char type, char character);
int				ft_putchar(char c);
char			*ft_octchanger(unsigned long num);
int				ft_numlen(long long n);
char			*ft_itoa(int n);
int				ft_isdigit(int c);
char			*ft_hexchanger(unsigned long num);
void			ft_putstr_fd(char *s, int fd);
void			*ft_calloc(size_t count, size_t size);
void			ft_bzero(void *ptr, size_t n);
int				ft_atoi(char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				ft_isspace(int c);
void			*ft_memalloc(size_t size);
#endif

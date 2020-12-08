/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 09:32:57 by seohchoi          #+#    #+#             */
/*   Updated: 2020/12/08 10:52:54 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

char			*ft_utoa(long long n);
int				ft_tolower(int c);
int	ft_compare(char *s1, char *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtolower(char *str);
size_t			ft_strlen(const char *str);
int				ft_strcat(char *dest, char const *src);
int				ft_strlcat(char *dst, const char *src, int dstsize);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_free(char *s1, char const *s2);
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
int				ft_ispipe(int c);
int				ft_isbracket(int c);
void			*ft_memalloc(size_t size);
char                    **ft_split(char const *s, char c);
char			*ft_strnew(size_t size);
char			*ft_strtrim(char *s1, char *set);
void			ft_strdel(char **as);
void			ft_splitdel(char ***s);

typedef struct		s_list
{
	void			*content;
	size_t			*content_size;
	struct s_list	*next;
}						t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **upc, t_list *new);
void	ft_lstadd_front(t_list **upc, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdel(t_list **alst, void (*del)(void *));
void	ft_lstdelone(t_list *alst, void (*del)(void *));

#endif

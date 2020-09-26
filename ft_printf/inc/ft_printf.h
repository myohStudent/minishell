/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seohchoi <seohchoi@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 09:38:39 by seohchoi          #+#    #+#             */
/*   Updated: 2020/04/23 02:46:49 by seohchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>

struct				s_flag
{
	int				hyphen;
	int				zero;
	int				minus;

	int				width;
	int				conlen;
	int				pre;

	int				relen;

	char			type;
	int				ispre;
	int				ishash;

	char			character;
	int				number;
	unsigned int	unumber;
	unsigned long	ulong;

}					t_flag;

int					ft_printf(const char *input, ...);

void				ft_getter(const char *input, va_list ptr);
char				ft_type_getter(const char *input);
int					ft_width_getter(const char *input, va_list ptr);
void				ft_precision_getter(const char *input, \
					va_list ptr, char type);
void				ft_arg_getter(char type, va_list ptr);

char				*ft_width_flag(int contentlen, int index, char *src);
char				*ft_pre_flag(int contentlen, int index, char *src);
char				*ft_zero_flag(char *src);
char				*ft_ox_hash_flag(char *result, char type);
char				*ft_neg_flag(char *result);
char				*ft_hyphen_flag(int contentlen, char *result, char *src);
char				*ft_hashwithzero_flag(char *result, char *src);

void				ft_initialize(void);
char				*ft_spe_checker(char type, va_list ptr);
void				ft_flag_checker(const char *input, va_list ptr, char type);
char				*ft_neg_checker(char *result, const char *input, char type);
int					ft_flagchr(const char *input, char *flag);

#endif

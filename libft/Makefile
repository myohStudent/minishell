# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/02 10:13:24 by myoh              #+#    #+#              #
#    Updated: 2020/03/03 14:43:31 by myoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror -I. -c
CC = gcc
SRC	 = ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_atoi.c \
				ft_strlen.c \
				ft_memcmp.c \
				ft_strncmp.c \
				ft_strdup.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strnstr.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memset.c \
				ft_memccpy.c \
				ft_memmove.c \
				ft_memchr.c \
				ft_calloc.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c

BNS	= ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c 

OBJ			= $(SRC:%.c=%.o)
OBB			= $(BNS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
		ar	rcs	$(NAME) $(OBJ)
$(OBJ):	$(SRC)
		gcc	$(CFLAGS) $(SRC)

$(OBB): $(BNS)
		gcc $(CFLAGS) $(BNS)

clean:
		rm -f $(OBJ) $(OBB)

fclean: clean 
		rm -f $(NAME)

re: fclean all

bonus:	$(OBB)
		ar	rcs $(NAME)	$(OBB)

.PHONY: clean fclean all re
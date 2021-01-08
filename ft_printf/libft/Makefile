NAME	=	libft.a
CC		=	gcc
FLAG	=	-Wall -Wextra -Werror
SRC		=	ft_hexchanger.c \
			ft_compare.c \
			ft_isdigit.c \
			ft_isspace.c \
			ft_itoa.c \
			ft_utoa.c \
			ft_tolower.c \
			ft_substr.c \
			ft_strtolower.c \
			ft_strlen.c \
			ft_strdel.c \
			ft_strlcat.c \
			ft_strjoin.c \
			ft_memalloc.c \
			ft_strdup.c \
			ft_trim.c \
			ft_strdchar.c \
			ft_strchr.c \
			ft_putstr.c \
			ft_putstr_fd.c \
			ft_putchar.c \
			ft_octchanger.c\
			ft_calloc.c\
			ft_bzero.c\
			ft_strncmp.c\
			ft_memcpy.c\
			ft_atoi.c\
			ft_putstr_fd.c \
			ft_split.c \
			ft_splitdel.c \
			ft_strnew.c \
			ft_strtrim.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstadd_back.c \
			ft_lstsize.c \
			ft_lstclear.c \
			ft_lstdel.c \
			ft_lstdelone.c \

INC		=	libft.h

OBJS	=	${SRC:.c=.o}

$(NAME) : ${OBJS}
	@ar rcs ${NAME} ${OBJS}

%.o		:	%.c $(INC)
	@$(CC) $(FLAG) -c $< -o $@

all		:	${NAME}

clean	:
	 rm -f ${OBJS}
fclean	:	clean
	 rm -f ${NAME}
re		:	fclean all

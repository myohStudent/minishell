NAME	=	libftprintf.a
CC		=	gcc
FLAG	=	-Wall -Wextra -Werror

SRC_DIR  =   ./src
SRC_NAME =	ft_printf.c \
			ft_getter.c \
			ft_flag.c ft_flag2.c \
			ft_checker.c
SRC		 = $(addprefix $(SRC_DIR)/, $(SRC_NAME))

OBJ_DIR  = ./obj
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ		 = $(addprefix $(OBJ_DIR)/, $(OBJ_NAME))

INCLUDE = -I ./inc/
LIBFT	= -L ./libft/

all		:	$(NAME)

$(NAME)	: $(OBJ)
	@$(MAKE) -C ./libft all
	@cp ./libft/libft.a ./$(NAME)
	ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAG) $(INCLUDE) -o $@ -c $<

clean	:
	@$(MAKE) -C ./libft clean
	rm -f $(OBJS)
fclean	:
	@$(MAKE) -C ./libft fclean
	rm -rf ./obj $(NAME)
re		:	fclean	all

.PHONY: all clean fclean re

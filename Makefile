NAME	=	minishell

SRCS	=	main.c \
			welcome_shell.c \
			sig_handler.c \

PARSE_DIR	=   ./parse_input
PARSE_FILE	=	get_input.c \
				parse_input.c
PARSE		= $(addprefix $(PARSE_DIR)/, $(PARSE_FILE))

OBJ_PARSE = $(PARSE:%.c=%.o)

LIB = -L ./libft -lft

all:	$(NAME)

$(NAME): $(OBJ_PARSE)
	@$(MAKE) -C ./libft all
	gcc $(SRCS) $(OBJ_PARSE) $(LIB) -o minishell

.c.o:
	gcc $(LIB) -o $@ -c $<

clean:
	@$(MAKE) -C ./libft clean

fclean:
	@$(MAKE) -C ./libft fclean
	rm -rf minishell

re:
	@$(MAKE) fclean all

.PHONY: all fclean clean re
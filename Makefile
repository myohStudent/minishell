NAME	=	minishell

SRCS	=	main.c \
			welcome_shell.c \
			sig_handler.c \

CMD_DIR	=   ./cmd_handler
CMD_FILE	=	cmd_handler.c \
				parse_input.c
CMD		= $(addprefix $(CMD_DIR)/, $(CMD_FILE))

OBJ_CMD = $(CMD:%.c=%.o)

LIB = -L ./libft -lft

all:	$(NAME)

$(NAME): $(OBJ_CMD)
	@$(MAKE) -C ./libft all
	gcc $(SRCS) $(OBJ_CMD) $(LIB) -o minishell

.c.o:
	gcc $(LIB) -o $@ -c $<

clean:
	@$(MAKE) -C ./libft clean
	rm -f $(OBJ_CMD) 
#여기다가 OBJ_CMD이 아닌 objs의 종합을 넣어야 함

fclean:
	@$(MAKE) -C ./libft fclean
	rm -rf $(NAME) $(OBJ_CMD)

re:
	@$(MAKE) fclean all

.PHONY: all fclean clean re
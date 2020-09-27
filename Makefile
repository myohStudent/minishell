NAME	=	minishell

SRCS	=	main.c \
				welcome_shell.c \
				sig_handler.c \
				initenv.c \
				cmd_env.c \

CMD_DIR	=	./cmd_handler
CMD_FILE	=	cmd_handler.c \
						parse_input.c \

CMD		= $(addprefix $(CMD_DIR)/, $(CMD_FILE))

OBJ_CMD = $(CMD:%.c=%.o)

LIB = -L ./ft_printf -lftprintf

all:	$(NAME)

$(NAME): $(OBJ_CMD)
	@$(MAKE) -C ./ft_printf all
	gcc $(SRCS) $(OBJ_CMD) $(LIB) -o minishell

clean:
	@$(MAKE) -C ./ft_printf clean
	rm -f $(OBJ_CMD) 
#여기다가 OBJ_CMD이 아닌 objs의 종합을 넣어야 함

fclean:
	@$(MAKE) -C ./ft_printf fclean
	rm -rf $(NAME) $(OBJ_CMD)

re:
	@$(MAKE) fclean all

.PHONY: all fclean clean re
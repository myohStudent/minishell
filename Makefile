NAME	=	minishell

SRCS	=	main.c \
			welcome_shell.c \
			sig_handler.c \
			parse_input.c \

all:	$(NAME)

$(NAME):
	@$(MAKE) -C ./libft all
	gcc $(SRCS) -L ./libft -lft -o minishell

clean:
	@$(MAKE) -C ./libft clean

fclean:
	@$(MAKE) -C ./libft fclean
	rm -rf minishell

re:
	@$(MAKE) fclean all

.PHONY: all fclean clean re
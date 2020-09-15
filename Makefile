NAME	=	minishell

SRCS	=	main.c \
			initenv.c \
			welcome_shell.c \

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
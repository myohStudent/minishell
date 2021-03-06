
NAME	=	minishell

SRCS	=	main.c \
				welcome_shell.c \
				sig_handler.c \

CMD_DIR	=	./cmd_handler
CMD_FILE	=	cmd_handler.c \
				cmd_handler2.c \
				cmd_handler3.c \
				parse_input.c \
				handler_utils.c \
				handler_utils2.c \
				has_utils.c \
				init.c \
				quote_utils.c \
				parse_quote.c \
				parse_utils.c \
				parse_utils2.c \
				parse_utils3.c \

CMD		= $(addprefix $(CMD_DIR)/, $(CMD_FILE))
OBJ_CMD = $(CMD:%.c=%.o)

EXE_DIR	=	./cmd_execute
EXE_FILE	=	cmd_env.c \
				cmd_exit.c \
				cmd_pwd.c \
				cmd_cd.c \
				cmd_echo.c \
				pipe_utils.c \
				redir_execute.c \
				dollar_exec.c \
				dollar_exec_with_quote.c \
				cmd_export.c \
				cmd_export2.c \
				cmd_unset.c \

EXE		= $(addprefix $(EXE_DIR)/, $(EXE_FILE))
OBJ_EXE = $(EXE:%.c=%.o)

LIB = -L ./ft_printf -lftprintf

FLAG	=	-Wall -Wextra -Werror

all:	$(NAME)

$(NAME): $(OBJ_CMD) $(OBJ_EXE)
	@$(MAKE) -C ./ft_printf all
	gcc $(FLAG) $(SRCS) $(OBJ_CMD) $(OBJ_EXE) $(LIB) -o minishell

clean:
	@$(MAKE) -C ./ft_printf clean
	rm -f $(OBJ_CMD) $(OBJ_EXE)
#여기다가 OBJ_CMD이 아닌 objs의 종합을 넣어야 함

fclean:
	@$(MAKE) -C ./ft_printf fclean
	rm -rf $(NAME) $(OBJ_CMD) $(OBJ_EXE)

re:
	@$(MAKE) fclean all

.PHONY: all fclean clean re
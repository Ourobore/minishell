SRCS	=	$(DIR)/prompt.c \
			$(DIR)/call_builtin.c \
			$(DIR)/builtin_echo.c \
			$(DIR)/builtin_exit.c \
			$(DIR)/builtin_pwd.c \
			$(DIR)/builtin_cd.c	\
			$(DIR)/builtin_env.c \
			$(DIR)/builtin_export.c \
			$(DIR)/builtin_unset.c \
			$(DIR)/envp_utils.c \
			$(DIR)/execute.c \
			$(DIR)/execute_utils.c \
			$(DIR)/env_variable.c \
			$(DIR)/pipes.c  \
			$(DIR)/redirection.c \
			$(DIR)/cmd_list.c \
			$(DIR)/parsing.c

DIR		=	./srcs

INCLUDE	=	-I .

OBJS	:=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

FSAN	=	-g3 -fsanitize=address

NAME	=	minishell

LIBFT	=	libft/libft.a

#%.o: %.c
#			$(CC) $(CFLAGS) $< -o $@

all		:	$(NAME)

$(NAME)	:	$(OBJS) main.c
			@make -C ./libft
			$(CC) $(CFLAGS) -g3 -lncurses main.c $(OBJS) $(LIBFT) $(INCLUDE) -o $(NAME)

fsan	:	$(OBJS) main.c
			@make -C ./libft
			$(CC) $(CFLAGS) $(FSAN) -lncurses main.c $(OBJS) $(LIBFT) $(INCLUDE) -o $(NAME)

leaks	:	$(NAME)
			valgrind --tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes ./$(NAME)

clean	:
			@make clean -C ./libft
			rm -rf $(OBJS)

fclean	:	clean
			@make fclean -C ./libft
			rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all fsan leaks clean fclean re

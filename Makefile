SRC		=	prompt.c

DIR		=	./srcs

INCLUDE	=	-I .

OBJS	:=	${SRCS:.c=.o}

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

NAME	=	minishell

LIBFT	=	./libft/libft.a

%.o: %.c
			$(CC) $(CFLAGS) $< -o $@

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			@make -C ./libft
			$(CC) $(CFLAGS) main.c $(OBJS) $(INCLUDE) -L$(LIBFT) -o $(NAME)

clean	:
			@make clean -C ./libft
			rm -rf $(OBJS)

fclean	:	clean
			@make fclean -C ./libft
			rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

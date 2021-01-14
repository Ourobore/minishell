SRCS	= $(DIR)/ft_atoi.c \
			$(DIR)/ft_isalpha.c \
			$(DIR)/ft_isalnum.c \
			$(DIR)/ft_isascii.c \
			$(DIR)/ft_isdigit.c \
			$(DIR)/ft_isprint.c \
			$(DIR)/ft_strchr.c \
			$(DIR)/ft_strlen.c \
			$(DIR)/ft_strcmp.c \
			$(DIR)/ft_strncmp.c \
			$(DIR)/ft_strrchr.c \
			$(DIR)/ft_toupper.c \
			$(DIR)/ft_tolower.c \
			$(DIR)/ft_strnstr.c \
			$(DIR)/ft_memset.c \
			$(DIR)/ft_bzero.c \
			$(DIR)/ft_memcpy.c \
			$(DIR)/ft_memccpy.c \
			$(DIR)/ft_memmove.c \
			$(DIR)/ft_memcmp.c \
			$(DIR)/ft_strlcat.c \
			$(DIR)/ft_strlcpy.c \
			$(DIR)/ft_calloc.c \
			$(DIR)/ft_strdup.c \
			$(DIR)/ft_substr.c \
			$(DIR)/ft_strjoin.c \
			$(DIR)/ft_strtrim.c \
			$(DIR)/ft_split.c \
			$(DIR)/ft_putchar_fd.c \
			$(DIR)/ft_putstr_fd.c \
			$(DIR)/ft_putendl_fd.c \
			$(DIR)/ft_putnbr_fd.c \
			$(DIR)/ft_itoa.c \
			$(DIR)/ft_strmapi.c \
			$(DIR)/ft_lstnew_bonus.c \
			$(DIR)/ft_lstadd_front_bonus.c \
			$(DIR)/ft_lstsize_bonus.c \
			$(DIR)/ft_lstlast_bonus.c \
			$(DIR)/ft_lstadd_back_bonus.c \
			$(DIR)/ft_lstdelone_bonus.c \
			$(DIR)/ft_lstclear_bonus.c \
			$(DIR)/ft_lstiter_bonus.c \
			$(DIR)/ft_lstmap_bonus.c \
			$(DIR)/get_next_line.c

DIR		=	./srcs

#ft_memchr.c \

OBJS	:=	$(SRCS:.c=.o)

INCLUDE	=	-I .

NAME	=	libft.a

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -rf

all		:	$(NAME)

$(NAME):	$(OBJS)
			ar rc $(NAME) $(OBJS)
			ranlib $(NAME)

clean	:
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(NAME) a.out

re		:	fclean all

.PHONY	:	all clean fclean re

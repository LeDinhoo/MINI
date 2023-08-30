

.PHONY: 		clean fclean re bonus

NAME 			= libft.a
CFLAGS 			= -Wall -Wextra -Werror

LIST_HEADERS 	= libft.h

SRCS			=	ft_atoi.c			\
					ft_atol.c			\
					ft_bzero.c			\
					ft_calloc.c			\
					ft_isdigit.c		\
					ft_itoa.c			\
					ft_lstadd_back.c	\
					ft_lstadd_front.c	\
					ft_memchr.c			\
					ft_memcmp.c			\
					ft_memcpy.c			\
					ft_memmove.c		\
					ft_memset.c			\
					ft_putchar_fd.c		\
					ft_putendl_fd.c		\
					ft_putstr_fd.c		\
					ft_split.c			\
					ft_strdup.c			\
					ft_strichr.c		\
					ft_striteri.c		\
					ft_strjoin.c		\
					ft_strlcat.c		\
					ft_strlcpy.c		\
					ft_strlen.c			\
					ft_strmapi.c		\
					ft_strncmp.c		\
					ft_strnstr.c		\
					ft_strrchr.c		\
					ft_strchr.c			\
					ft_strtrim.c		\
					ft_substr.c			\
					ft_isspace.c		\
					ft_strcpy.c			\
					ft_strcmp.c			\

DIR_HEADERS 	= ./
DIR_OBJS 		= .objs/
RM				= rm -rf

# ---------------------------------------------------

OBJS 			= $(addprefix $(DIR_OBJS), $(SRCS:.c=.o))

all : 			$(NAME)

$(NAME):		$(DIR_OBJS) $(OBJS) $(LIST_HEADERS)
				$(AR) rcs $(NAME) $(OBJS)

$(DIR_OBJS):
				mkdir -p $(DIR_OBJS)

bonus: 			$(DIR_OBJS) $(OBJS_B) $(LIST_HEADERS)
				$(AR) rcs $(NAME) $(OBJS_B)

$(DIR_OBJS)%.o: %.c $(LIST_HEADERS) Makefile
				$(CC) $(CFLAGS) -c $< -o $@ -I $(DIR_HEADERS)

# ----------------------------------------------------- #

clean:
				$(RM) $(OBJS) $(OBJS_B)

fclean: clean
				$(RM) $(NAME)

re: fclean
				$(MAKE) all

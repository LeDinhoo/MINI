

.PHONY: 		clean fclean re bonus

NAME 			= libftprintf.a
CFLAGS 			= -Wall -Wextra -Werror -g3

LIST_HEADERS 	=	ft_printf.h		\

SRCS 			=	ft_printf.c				\
					ft_printf_utils.c

SRCS_B =


DIR_HEADERS 	=	./			\

INCLUDES		=	${addprefix -I, ${DIR_HEADERS}}

DIR_OBJS 		= .objs/
RM				= rm -rf

# ---------------------------------------------------

OBJS 			= $(addprefix $(DIR_OBJS), $(SRCS:.c=.o))
OBJS_B 			= $(addprefix $(DIR_OBJS), $(SRCS_B:.c=.o))

all :
				${MAKE} $(NAME)

$(NAME):		$(DIR_OBJS) $(OBJS) $(LIST_HEADERS) Makefile
				$(AR) rcs $(NAME) $(OBJS)

$(DIR_OBJS):
				mkdir -p $(DIR_OBJS)

$(DIR_OBJS)%.o: %.c $(LIST_HEADERS) Makefile
				$(CC) $(CFLAGS) -c $< -o $@ ${INCLUDES}

# ----------------------------------------------------- #

clean:
				${MAKE}
				$(RM) $(OBJS) $(OBJS_B)

fclean: clean
				${MAKE}
				$(RM) $(NAME) $(DIR_OBJS)

re: fclean
				$(MAKE) all


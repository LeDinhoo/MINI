.PHONY: all clean fclean re

NAME = minishell
CC = gcc
CFLAGS = 
INCLUDE_DIR = include
INCLUDES = -I$(INCLUDE_DIR) 

SRC_DIR = .
OBJ_DIR = .obj

LIBFT_A = libft.a
LIBFT_DIR = utils/libft/
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_A))

PRINTF_A = libftprintf.a
PRINTF_DIR = utils/ft_printf/
PRINTF = $(addprefix $(PRINTF_DIR), $(PRINTF_A))

SRC = 	$(SRC_DIR)/main.c \
		$(SRC_DIR)/srcs/parsing/init.c \
		$(SRC_DIR)/srcs/parsing/command_processing.c \
		$(SRC_DIR)/srcs/parsing/memory_management.c \
		$(SRC_DIR)/srcs/parsing/node_management.c \
		$(SRC_DIR)/srcs/parsing/path.c \
		$(SRC_DIR)/srcs/parsing/print_helper.c \
		$(SRC_DIR)/srcs/parsing/string_split.c \
		$(SRC_DIR)/srcs/parsing/token_identification.c \
		$(SRC_DIR)/srcs/builtins/echo.c \
		$(SRC_DIR)/srcs/builtins/cd.c \
		$(SRC_DIR)/srcs/exec/exec_builtin.c \
		$(SRC_DIR)/srcs/exec/exec.c \

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_SRC = $(wildcard $(LIBFT_DIR)*.c)
LIBFT_OBJ = $(LIBFT_SRC:$(LIBFT_DIR)%.c=$(LIBFT_DIR).objs/%.o)
LIBFT_DEPS = $(LIBFT_OBJ:.o=.d)

PRINTF_SRC = $(wildcard $(PRINTF_DIR)*.c)
PRINTF_OBJ = $(PRINTF_SRC:$(PRINTF_DIR)%.c=$(PRINTF_DIR).objs/%.o)
PRINTF_DEPS = $(PRINTF_OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) $(INCLUDES)  $(OBJ) $(LIBFT) $(PRINTF) -lreadline -o $@
	@echo "Compilation terminée avec succès ! ✔️"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

$(LIBFT): $(LIBFT_OBJ)
	@$(MAKE) -C $(LIBFT_DIR) -s
	@echo "Compilation de libft terminée ! ✔️"

$(PRINTF): $(PRINTF_OBJ)
	@$(MAKE) -C $(PRINTF_DIR) -s
	@echo "Compilation de ft_printf terminée ! ✔️"

$(LIBFT_DIR).objs/%.o: $(LIBFT_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

$(PRINTF_DIR).objs/%.o: $(PRINTF_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

force: ;

clean:
	@echo "Suppression des fichiers objets... 🗑️"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean -s
	@$(MAKE) -C $(PRINTF_DIR) clean -s

fclean: clean
	@echo "Suppression du programme final... 🗑️"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean -s
	@$(MAKE) -C $(PRINTF_DIR) fclean -s

re: fclean all

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/srcs
	@mkdir -p $(OBJ_DIR)/srcs/parsing/
	@mkdir -p $(OBJ_DIR)/srcs/builtins/
	@mkdir -p $(OBJ_DIR)/srcs/exec/
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(LIBFT_DIR).objs
	@mkdir -p $(PRINTF_DIR).objs

-include $(LIBFT_DEPS) $(PRINTF_DEPS)

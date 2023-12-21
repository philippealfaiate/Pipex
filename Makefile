NAME		=	pipex

CC			=	gcc -g

FLAG		=	-Wall -Wextra -Werror

LIBFT_PATH	=	./libft/

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

C_FILE		=	pipex.c pathfinder.c error.c

# SRC_DIR		=	./core/
SRC_DIR		=

INC_DIR		=	./header/

VPATH = src

SRC			=	$(addprefix $(SRC_DIR),$(C_FILE))

OBJ_DIR 	= obj
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
# OBJ			=	$(SRC:.c=.o)

# .c.o:
# 	@mkdir -p $(OBJ_DIR)
# 	$(CC) $(FLAG) -c $< -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

lib:
	@make -C $(LIBFT_PATH)

# $(NAME): lib $(OBJ)
$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT_LIB) -o $(NAME)

clean:
	@make clean -sC $(LIBFT_PATH)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re

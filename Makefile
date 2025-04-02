NAME = ft_ssl

SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = $(wildcard $(SRC_DIR)/*.c)

INCLUDE = ./include
INCLUDE_LIBFT = $(LIBFT_DIR)/includes

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

DEPS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.d)

CFLAGS = -Wall -Wextra -Werror -MMD -MP -fsanitize=address
LFLAGS = -L$(LIBFT_DIR) -lft

all: $(LIBFT) $(OBJ_DIR) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -I$(INCLUDE_LIBFT) -c $< -o $@

-include $(DEPS)

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

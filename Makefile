NAME = ft_ssl

SRC_DIR = src

OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c)

INCLUDE = ./include

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

DEPS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.d)

CFLAGS = -Wall -Wextra -Werror -MMD -MP

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

-include $(DEPS)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

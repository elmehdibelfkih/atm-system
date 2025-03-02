NAME = atm-system
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -fsanitize=leak -MMD -MP
LDFLAGS = -lsqlite3
SRC_DIR = src
OBJ_DIR = obj

SRC = $(shell find $(SRC_DIR) -name "*.c")
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
DEP = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(DEP)
fclean: clean
	rm -f $(NAME)
re: fclean all
run: all
	./$(NAME)
-include $(DEP)
.PHONY: all clean fclean re
NAME = atm-system
SRC = $(shell find . -name "*.c")
OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror
LDFLAGS = -lsqlite3
all: $(NAME)
$(NAME): $(OBJ)
	cc $(FLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
%.o: %.c
	cc $(FLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re

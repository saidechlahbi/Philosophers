CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Files
FILES =  algorithme_bonus.c philo_bonus.c init_all_bonus.c parsing_bonus.c

# Object files
OBJ = $(FILES:.c=.o)

# Name
NAME = philo

# Header
HEADER =  philo_bonus.h


# Rules
all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
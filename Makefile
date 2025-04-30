CC = cc
FLAGS = -Wall -Wextra -Werror

# Files
FILES =   parsing.c  philo.c 

# Object files
OBJ = $(FILES:.c=.o)

# Name
NAME = philo

# Header
HEADER =  philo.h


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
CC = cc
FLAGS = -Wall -Wextra -Werror

# Files
FILES =   init_all.c  parsing.c  philo.c routine.c tools.c monitor.c clean.c \
		init_chopstick.c 

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

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
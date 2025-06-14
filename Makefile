CC=cc
FLAGS=-Wall -Wextra -Werror -g -fsanitize=thread
SRC=	philo.c \
		parsing.c \
		philo_utils1.c \
		philo_utils2.c \
		philo_utils3.c \
		to_int.c \
		routing.c
OBJ=$(SRC:.c=.o)
NAME= philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
CC=cc
FLAGS=-Wall -Wextra -Werror -g -fsanitize=address
SRC=	philo.c \
		parsing.c \
		philo_utils1.c \
		philo_utils2.c \
		philo_utils3.c \
		to_int.c 
OBJ=$(SRC:.c=.o)
G = $(shell tput setaf 2)
R = $(shell tput setaf 1)
Y = $(shell tput setaf 3)
NAME= philo

all: $(NAME)
	@echo $(G) all functions are done

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	@echo $(Y) compailing file $< ... done
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo $(R) "Cleaning objects"
	@rm -f $(OBJ)

fclean: clean
	@echo $(R) "Cleaning $(NAME)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
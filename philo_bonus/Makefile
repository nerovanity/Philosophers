# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/18 14:39:23 by ihamani           #+#    #+#              #
#    Updated: 2025/07/02 19:39:50 by ihamani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
FLAGS=-Wall -Wextra -Werror #-g -fsanitize=address
SRC=	philo_bonus.c \
		philo_utils_bonus.c \
		philo_utils2_bonus.c \
		philo_utils3_bonus.c \
		routine_bonus.c	\
		parsing_bonus.c \
		to_int_bonus.c
OBJ=$(SRC:.c=.o)
NAME= philo_bonus

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo_bonus.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
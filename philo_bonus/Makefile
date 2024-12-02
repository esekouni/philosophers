# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 11:04:09 by esekouni          #+#    #+#              #
#    Updated: 2023/05/13 15:01:50 by esekouni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

FLAGS = -Wall -Werror -Wextra

CC = cc $(FLAGS)

SRC = philosophers_bonus.c \
		fonction_bonus.c \
		fonction_bonus_3.c \
		fonction2.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) philosophers_bonus.h
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean :
		rm -rf $(OBJ)

fclean : clean
		rm -rf $(NAME)

re : fclean all
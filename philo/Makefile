# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esekouni <esekouni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 21:33:26 by esekouni          #+#    #+#              #
#    Updated: 2023/05/13 15:01:45 by esekouni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -Wall -Werror -Wextra

CC = cc $(FLAGS)

SRC = philosophers.c \
		fonction.c \
		fonction1.c \
		fonction2.c 

OBJ = $(SRC:.c=.o) 
		
all : $(NAME)

$(NAME) : $(OBJ) philosophers.h
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean :
		rm -rf $(OBJ)

fclean : clean
		rm -rf $(NAME)

re : fclean all
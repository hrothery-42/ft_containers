# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 09:24:02 by hrothery          #+#    #+#              #
#    Updated: 2022/12/16 14:22:41 by hrothery         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_containers

SRC = tests/vector_tests.cpp

OBJ = $(SRC:.cpp=.o)

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

all : $(NAME)

$(NAME) : $(OBJ) $(SRC)
	$(CC) $(CFLAGS) $(OBJ) -o $@

clean : 
	rm -f $(OBJ)

fclean : clean 
	rm -f $(NAME)

re : fclean all

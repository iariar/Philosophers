# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iariss <iariss@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/14 11:44:36 by iariss            #+#    #+#              #
#    Updated: 2021/06/16 08:42:02 by iariss           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = philo_bonus.a
EXEC    = philo_bonus
CC      = gcc
CFLAGS  = -Wall -Werror -Wextra
HEADER = file.h

SRC = philo_bonus.c check.c threads.c print.c
	
OBJ = $(SRC:.c=.o)


all : $(NAME)

$(NAME): $(HEADER) $(OBJ) 

	ar rcs $(NAME) $(OBJ)
	$(CC) $(CFLAGS) $(SRC) $(NAME) -o $(EXEC) 

clean:
	rm -f $(OBJ) $(NAME)

fclean: clean
	rm -f $(EXEC)

re: fclean all
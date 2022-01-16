# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iariss <iariss@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/14 11:44:36 by iariss            #+#    #+#              #
#    Updated: 2021/07/26 10:15:57 by iariss           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC    = philo_bonus
CC      = gcc
CFLAGS  = -Wall -Werror -Wextra
HEADER = file.h

SRC = philo_bonus.c check.c processes.c print.c
	
OBJ = $(SRC:.c=.o)


all : $(EXEC)

$(EXEC): $(HEADER) $(OBJ) 

	$(CC) $(CFLAGS) $(SRC) -o $(EXEC) 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXEC)

re: fclean all
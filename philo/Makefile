# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 18:23:18 by anaraujo          #+#    #+#              #
#    Updated: 2023/03/14 22:02:05 by anaraujo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

CC := cc -pthread
CFLAGS := -Wall -Werror -Wextra -g 

SRCS := ./src/check_args.c		./src/init.c				\
		./src/philosophers.c	./src/threads.c			\
		./src/utils.c			./src/philo_functions.c	\
		./src/time_utils.c		


OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	echo "\033[1m $(NAME) ready \033[0m"

clean:
		rm -rf $(OBJS)
		echo "OBJS deleted"

fclean: clean
		rm -rf $(NAME)
		echo "$(NAME) deleted"

re: fclean all

.SILENT:
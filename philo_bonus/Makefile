# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 18:23:18 by anaraujo          #+#    #+#              #
#    Updated: 2023/03/05 14:09:09 by anaraujo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo_bonus

CC := cc -pthread
CFLAGS := -Wall -Werror -Wextra -g

SRCS := ./srcs/check_args.c		./srcs/init.c				\
		./srcs/philosophers.c	./srcs/threads.c			\
		./srcs/utils.c			./srcs/philo_functions.c	\
		./srcs/time_utils.c		

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -lm $(OBJS) -o $(NAME)
	echo "\033[1m $(NAME) ready \033[0m"

clean:
		rm -rf $(OBJS)
		echo "OBJS deleted"

fclean: clean
		rm -rf $(NAME)
		echo "$(NAME) deleted"

re: fclean all

.SILENT:
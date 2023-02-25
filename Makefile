# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 18:23:18 by anaraujo          #+#    #+#              #
#    Updated: 2023/02/25 22:05:45 by anaraujo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
BONUS := philo_bonus

CC := cc -pthread
CFLAGS := -Wall -Werror -Wextra -g

SRCS := ./srcs/check_args.c		./srcs/init.c				\
		./srcs/philosophers.c	./srcs/threads.c			\
		./srcs/utils.c			./srcs/philo_functions.c	\
		./srcs/time_utils.c		

SRCS_BONUS := 


OBJS := $(SRCS:.c=.o)

OBJS_BONUS := $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -lm $(OBJS) -o $(NAME)
	echo "\033[1m $(NAME) ready \033[0m"

bonus: $(BONUS)

$(BONUS): $(OBJS_BONUS)
		$(CC) $(CFLAGS) -lm $(OBJS_BONUS) -o $(BONUS)
		echo "\033[1m $(BONUS) ready \033[0m"

clean:
		rm -rf $(OBJS)
		rm -rf $(OBJS_BONUS)
		echo "OBJS deleted"

fclean: clean
		rm -rf $(NAME)
		rm -rf $(BONUS)
		echo "$(NAME) deleted"
		echo "$(BONUS) deleted"

re: fclean all

.SILENT:
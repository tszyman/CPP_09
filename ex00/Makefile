# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tszymans <tszymans@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/10 19:27:57 by tszymans          #+#    #+#              #
#    Updated: 2026/03/12 21:39:41 by tszymans         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = btc

CC      = c++
CFLAGS  = -Wall -Wextra -Werror -std=c++98

SRCS    = main.cpp\
			BitcoinExchange.cpp

OBJS    = $(SRCS:.cpp=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

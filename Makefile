# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arendon- <arendon-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 11:39:33 by arendon-          #+#    #+#              #
#    Updated: 2022/02/11 16:41:14 by arendon-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = server
NAME2 = client

CC = gcc

FLAGS = -Wall -Wextra -Werror
FT = -Ilibft -Llibft -lft

OBJS1 = $(patsubst %.c, %.o, $(SRCS1))
OBJS2 = $(patsubst %.c, %.o, $(SRCS2))

SRCS1 = server.c 
SRCS2 = client.c

FT_PATH = ./libft/

all: $(NAME1) $(NAME2)

$(NAME1): libft/libft.a $(OBJS1)
	$(CC) $(OBJS1) ${FT} -o $(NAME1)

$(NAME2): libft/libft.a $(OBJS2)
	$(CC) $(OBJS2) ${FT} -o $(NAME2)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS1) $(OBJS2)
	${MAKE} -C ${FT_PATH} clean

fclean: clean
	rm -f $(NAME1) $(NAME2)
	${MAKE} -C ${FT_PATH} fclean

re: fclean all

libft/libft.a:
	${MAKE} -C ${FT_PATH}

.PHONY: all clean fclean re libft

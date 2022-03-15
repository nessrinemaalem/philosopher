# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imaalem <imaalem@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 14:24:37 by imaalem           #+#    #+#              #
#    Updated: 2022/03/14 18:55:08 by imaalem          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosopher

CFLAGS = -Wall -Werror -Wextra -pthread -I philosopher.h 

SRC =	main.c utils_ft.c parsing.c init_join.c tread_management.c \
		everyday_routine.c time.c routine_control.c extract_arg.c\

OBJ = $(SRC:.c=.o) 

all : $(NAME)

$(NAME) : $(OBJ)
			clang -o $(NAME) $(OBJ) $(CFLAGS)

clean :
			rm -rf $(OBJ)

fclean : clean
			rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re

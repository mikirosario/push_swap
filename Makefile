# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/05 20:32:49 by miki              #+#    #+#              #
#    Updated: 2021/05/09 21:53:41 by mrosario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = checker

SRCDIR = ./src/checker

SRC = $(SRCDIR)/main.c $(SRCDIR)/generate_stacks.c $(SRCDIR)/moves/s.c \

LIBFT = ./src/libft/libft.a

OBJ = $(SRC:.c=.o)

CFLAG = -Wall -Werror -Wextra

LIBS = -I ./includes -I ./src/libft/includes -L ./src/libft -lft -ltermcap

$(NAME): $(LIBFT)
	gcc $(CFLAG) $(SRC) -o $(NAME) $(LIBS) 

$(LIBFT):
	make -C ./src/libft
	make clean -C ./src/libft

all: $(NAME)

debug: $(LIBFT)
	#gcc $(CFLAG) $(SRC) -g3 -fsanitize=address -o $(NAME) $(LIBS)
	gcc $(CFLAG) $(SRC) -g -o $(NAME) $(LIBS)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)
	make fclean -C ./src/libft

re: fclean all

rebug: fclean debug

.PHONY: all debug clean fclean re rebug
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/05 20:32:49 by miki              #+#    #+#              #
#    Updated: 2021/05/14 22:15:48 by mrosario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = chkpsh

CHKNAME = checker
PSHNAME = push_swap

CHKDIR = ./src/checker
PSHDIR = ./src/push_swap

CHK =	$(CHKDIR)/main.c $(CHKDIR)/generate_stacks.c \
		$(CHKDIR)/get_instructions.c $(CHKDIR)/exit.c $(CHKDIR)/sort.c \
		$(CHKDIR)/moves/s.c $(CHKDIR)/moves/p.c $(CHKDIR)/moves/r.c \
		$(CHKDIR)/moves/rr.c \

PSH =	$(PSHDIR)/push_swap.c

LIBFT = ./src/libft/libft.a


CFLAG = -Wall -Werror -Wextra

LIBS = -I ./includes -I ./src/libft/includes -L ./src/libft -lft -ltermcap

$(NAME): $(LIBFT)
	gcc $(CFLAG) $(CHK) -o $(CHKNAME) $(LIBS)
	gcc $(CFLAG) $(PSH) -o $(PSHNAME) $(LIBS)

$(LIBFT):
	make -C ./src/libft
	make clean -C ./src/libft

all: $(NAME)

debug: $(LIBFT)
	#gcc $(CFLAG) $(CHK) -g3 -fsanitize=address -o $(NAME) $(LIBS)
	gcc $(CFLAG) $(CHK) -g -o $(CHKNAME) $(LIBS)
	gcc $(CFLAG) $(PSH) -g -o $(PSHNAME) $(LIBS)

clean:
	rm -f *.o

fclean: clean
	rm -f $(CHKNAME)
	rm -f $(PSHNAME)
	make fclean -C ./src/libft

re: fclean all

rebug: fclean debug

.PHONY: all debug clean fclean re rebug
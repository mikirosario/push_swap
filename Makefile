# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/05 20:32:49 by miki              #+#    #+#              #
#    Updated: 2021/06/15 20:09:57 by mrosario         ###   ########.fr        #
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

PSH =	$(PSHDIR)/push_swap.c $(PSHDIR)/generate_instructions.c \
		$(PSHDIR)/sort_conditions.c $(PSHDIR)/generate_position_map.c \
		$(PSHDIR)/get_relevant_numbers.c $(PSHDIR)/generate_stacks.c \
		$(PSHDIR)/sequence_stacks.c $(PSHDIR)/merge_sequence.c \
		$(PSHDIR)/exit.c $(PSHDIR)/push_lowers.c $(PSHDIR)/progress_bar.c \
		$(PSHDIR)/process_moves.c $(PSHDIR)/find_fastest.c \
		$(PSHDIR)/array_my_tree.c \
		$(PSHDIR)/three_numbers.c $(PSHDIR)/six_numbers.c \
		$(PSHDIR)/many_numbers.c \
		$(PSHDIR)/moves/s.c $(PSHDIR)/moves/p.c $(PSHDIR)/moves/r.c \
		$(PSHDIR)/moves/rr.c \

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

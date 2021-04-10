# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miki <miki@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/09 00:04:22 by mrosario          #+#    #+#              #
#    Updated: 2021/04/10 09:50:51 by miki             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	  ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
	  ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c \
	  ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c \
	  ft_toupper.c ft_calloc.c ft_strdup.c ft_strlcpy.c ft_substr.c \
	  ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
	  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	  ft_isspace.c ft_putchar.c ft_putstr.c ft_filler.c ft_strtolower.c \
	  ft_lluitoa_base.c ft_itoa_base.c ft_chrcmp.c ft_get_next_line.c \
	  ft_setbit.c ft_isbitset.c ft_del.c ft_getnextnum.c ft_strcmp.c \
	  ft_strncpy.c ft_free_split.c ft_memdup.c ft_thousep.c ft_skipspaces.c \
	  ft_skipdigits.c ft_iscntrl.c ft_get_window_size.c

BTREE = ft_bintree_add.c ft_bintree_search.c ft_bintree_free.c \
		ft_bintree_depth.c ft_bintree_print.c ft_bintree_termcaps.c \
		ft_bintree_balance.c

BSRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	   ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	   ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJ = $(SRC:.c=.o)

BOBJ = $(BSRC:.c=.o)

BTREEOBJ = $(BTREE:.c=.o)

CFLAG = -Wall -Werror -Wextra -g -I ./includes

all: $(NAME)

$(NAME):
	gcc $(CFLAG) -c $(SRC) $(BSRC) $(addprefix ./ft_bintree/,$(BTREE))
	ar -rcs $(NAME) $(OBJ) $(BOBJ) $(BTREEOBJ)

so:
	gcc $(CFLAG) -c $(SRC) $(BSRC) $(addprefix ./ft_bintree/,$(BTREE))
	gcc -shared -o libft.so $(OBJ) $(BOBJ) $(BTREEOBJ)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)
	rm -f libft.so

re: fclean all

.PHONY: all clean fclean re bonus

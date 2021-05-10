/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:07:56 by miki              #+#    #+#             */
/*   Updated: 2021/05/10 20:31:31 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "libft.h"
# include "ft_bintree.h"
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# define INSTRUCTIONS "sa:sb:ss:pa:pb:ra:rb:rr:rra:rrb:rrr"

typedef struct s_checker
{
	t_bstnode	*bintree;
	size_t		stack_size;
	t_list		*stack_a;
	t_list		*stack_b;
	//int			**stack_a;
	//int			**stack_b;
	t_list		*lst;
}				t_checker;

int	generate_stacks(char **argv, t_checker *checker);
int	exit_failure(char *error_msg, t_checker *checker);

/*
** Move to Libft
*/

void	ft_lst_removeone(t_list **alst, t_list *remove);

/*
** Movements
*/

void	sa_move(t_checker *checker);
void	sb_move(t_checker *checker);
void	ss_move(t_checker *checker);
void	pa_move(t_checker *checker);
void	pb_move(t_checker *checker);
void	ra_move(t_checker *checker);
void	rb_move(t_checker *checker);
void	rr_move(t_checker *checker);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:07:56 by miki              #+#    #+#             */
/*   Updated: 2021/06/08 23:35:16 by mrosario         ###   ########.fr       */
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
	t_list		*stack_a;
	t_list		*stack_b;
	t_list		*lst;
}				t_checker;

void		exit_failure(char *error_msg, t_checker *checker);
void		exit_success(t_checker *checker);
void		generate_stacks(char **argv, t_checker *checker);
void		get_instructions(t_checker *checker);
void		sort(t_checker *checker);

/*
** Movements
*/

void		sa_move(t_checker *checker);
void		sb_move(t_checker *checker);
void		ss_move(t_checker *checker);
void		pa_move(t_checker *checker);
void		pb_move(t_checker *checker);
void		ra_move(t_checker *checker);
void		rb_move(t_checker *checker);
void		rr_move(t_checker *checker);
void		rra_move(t_checker *checker);
void		rrb_move(t_checker *checker);
void		rrr_move(t_checker *checker);

#endif

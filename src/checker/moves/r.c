/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:49:50 by miki              #+#    #+#             */
/*   Updated: 2021/05/12 19:16:57 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/*
** This function moves the first member of stack a to the back and the second
** member to the front. If stack a has less than two members, nothing is done.
*/

void	ra_move(t_checker *checker)
{
	t_list	*first_member;
	t_list	*second_member;

	if (!checker->stack_a || !checker->stack_a->next)
		return ;
	first_member = checker->stack_a;
	second_member = checker->stack_a->next;
	checker->stack_a = second_member;
	ft_lstadd_back(&checker->stack_a, first_member);
}

/*
** This function is the same as ra_move, but with stack b.
*/

void	rb_move(t_checker *checker)
{
	t_list	*first_member;
	t_list	*second_member;

	if (!checker->stack_b || !checker->stack_b->next)
		return ;
	first_member = checker->stack_b;
	second_member = checker->stack_b->next;
	checker->stack_b = second_member;
	ft_lstadd_back(&checker->stack_b, first_member);
}

void	rr_move(t_checker *checker)
{
	ra_move(checker);
	rb_move(checker);
}

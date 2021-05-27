/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:49:50 by miki              #+#    #+#             */
/*   Updated: 2021/05/27 12:37:00 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** This function moves the first member of stack a to the back and the second
** member to the front. If stack a has less than two members, nothing is done.
*/

void	ra_move(t_pswap *pswap)
{
	t_list	*first_member;
	t_list	*second_member;

	if (!pswap->stack_a.stack || !pswap->stack_a.stack->next)
		return ;
	first_member = pswap->stack_a.stack;
	second_member = pswap->stack_a.stack->next;
	pswap->stack_a.stack = second_member;
	ft_lstadd_back(&pswap->stack_a.stack, first_member);
	add_move_to_list(pswap, "ra");
}

/*
** This function is the same as ra_move, but with stack b.
*/

void	rb_move(t_pswap *pswap)
{
	t_list	*first_member;
	t_list	*second_member;

	if (!pswap->stack_b.stack || !pswap->stack_b.stack->next)
		return ;
	first_member = pswap->stack_b.stack;
	second_member = pswap->stack_b.stack->next;
	pswap->stack_b.stack = second_member;
	ft_lstadd_back(&pswap->stack_b.stack, first_member);
	add_move_to_list(pswap, "rb");
}

void	rr_move(t_pswap *pswap)
{
	ra_move(pswap);
	rb_move(pswap);
	add_move_to_list(pswap, "rr");
}

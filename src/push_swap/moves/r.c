/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:49:50 by miki              #+#    #+#             */
/*   Updated: 2021/05/16 23:16:38 by mrosario         ###   ########.fr       */
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

	if (!pswap->stack_a || !pswap->stack_a->next)
		return ;
	first_member = pswap->stack_a;
	second_member = pswap->stack_a->next;
	pswap->stack_a = second_member;
	ft_lstadd_back(&pswap->stack_a, first_member);
}

/*
** This function is the same as ra_move, but with stack b.
*/

void	rb_move(t_pswap *pswap)
{
	t_list	*first_member;
	t_list	*second_member;

	if (!pswap->stack_b || !pswap->stack_b->next)
		return ;
	first_member = pswap->stack_b;
	second_member = pswap->stack_b->next;
	pswap->stack_b = second_member;
	ft_lstadd_back(&pswap->stack_b, first_member);
}

void	rr_move(t_pswap *pswap)
{
	ra_move(pswap);
	rb_move(pswap);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   six_numbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:18:16 by miki              #+#    #+#             */
/*   Updated: 2021/05/24 07:00:12 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"



int	push_to_stack_a(t_pswap *pswap)
{
	t_relevant *n;

	get_relevant_numbers(pswap);
	n = &pswap->num;
	if (n->a_first > n->b_first && are_contiguous(pswap, n->b_first, n->a_first))
		pa_move(pswap);
	else if (n->a_first < n->b_first && are_contiguous(pswap, n->a_first, n->b_first))
	{
		ra_move(pswap);
		pa_move(pswap);
	}
	else if (n->a_first < n->b_last && are_contiguous(pswap, n->a_first, n->b_last))
	{
		rr_move(pswap);
		pa_move(pswap);
	}
	else if (n->a_last > n->b_first && are_contiguous(pswap, n->b_first, n->a_last))
	{
		rra_move(pswap);
		pa_move(pswap);
	}
	else if (pswap->stack_b->next && n->a_last < n->b_second && are_contiguous(pswap, n->b_second, n->a_last))
	{
		sb_move(pswap);
		pa_move(pswap);
		ra_move(pswap);
	}
	else if (n->a_penult < n->b_first && are_contiguous(pswap, n->a_penult, n->b_first))
	{
		rra_move(pswap);
		pa_move(pswap);
		ra_move(pswap);
	}
	else if (pswap->stack_b->next && n->a_penult < n->b_last && are_contiguous(pswap, n->a_penult, n->b_last))
	{
		rrr_move(pswap);
		pa_move(pswap);
		ra_move(pswap);
	}
	else
		return (0);
	return (1);
}

/*
** This algorithm handles 4 to 6 numbers. The first one or two numbers are
** pushed to stack_b and the remaining numbers in stack_a are sorted using the
** three_numbers algorithm. The numbers in stack_a are then cycled using the
** ra_move until one of the stack_b numbers can be pushed into the right
** position in stack_a so that all of stack_a is in sequence and ready to be
** ordered by the sort_rotate_stack_a function.
*/

void	six_numbers(t_pswap *pswap)
{
	size_t		i;
	static char		stayout = 0;

	print_instructions(pswap);
	if (!stayout)
	{
		i = pswap->numbers - 3;
		while (i--)
			pb_move(pswap);
		while (!stack_a_is_sequenced(pswap))
			three_numbers(pswap);
		stayout = 1;
	}
	else if (pswap->stack_b_numbers > 0)
	{
		if (!push_to_stack_a(pswap))
			ra_move(pswap);
	}
}

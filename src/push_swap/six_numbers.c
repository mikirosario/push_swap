/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   six_numbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:18:16 by miki              #+#    #+#             */
/*   Updated: 2021/05/25 23:35:00 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"



int	push_to_stack_a(t_pswap *pswap)
{
	t_stack	*a;
	t_stack *b;

	get_relevant_numbers(pswap);
	a = &pswap->num_a;
	b = &pswap->num_b;
	if (a->first > b->first && are_contiguous(pswap, b->first, a->first))
		pa_move(pswap);
	else if (a->first < b->first && are_contiguous(pswap, a->first, b->first))
	{
		ra_move(pswap);
		pa_move(pswap);
	}
	else if (a->first < b->last && are_contiguous(pswap, a->first, b->last))
	{
		rr_move(pswap);
		pa_move(pswap);
	}
	else if (a->last > b->first && are_contiguous(pswap, b->first, a->last))
	{
		rra_move(pswap);
		pa_move(pswap);
	}
	else if (pswap->stack_b->next && a->last < b->second && are_contiguous(pswap, b->second, a->last))
	{
		sb_move(pswap);
		pa_move(pswap);
		ra_move(pswap);
	}
	else if (a->penult < b->first && are_contiguous(pswap, a->penult, b->first))
	{
		rra_move(pswap);
		pa_move(pswap);
		ra_move(pswap);
	}
	else if (pswap->stack_b->next && a->penult < b->last && are_contiguous(pswap, a->penult, b->last))
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   six_numbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:18:16 by miki              #+#    #+#             */
/*   Updated: 2021/06/08 22:52:45 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** This little ad-hoc function just takes a pointer to a move function and
** performs it, and then performs a push to a function. Basically... this is
** to save lines. Hey, at least I'm honest! xD
*/

static void	move_and_push(void (*move)(t_pswap *), t_pswap *pswap)
{
	if (move != NULL)
		move(pswap);
	pa_move(pswap);
}

/*
** This function analyses the relative positions of the first numbers of a and
** b and nearby numbers (second and last), and if two contiguous numbers are
** found the stacks are rotated as needed to bring the contiguous number in
** stack a or b to the right position to accept/send from stack_b.
**
** It's very similar to the push_to_stack_a conditions, except it also requires
** an extra rotation in stack_a to be performed after insertion.
**
** As with the other function, if no condition is met then 0 is returned to the
** caller. Otherwise, 1 is returned.
*/

static int	push_to_stack_a_and_rotate(t_pswap *pswap)
{
	t_stack	*a;
	t_stack	*b;

	a = &pswap->stack_a;
	b = &pswap->stack_b;
	if (pswap->stack_b.stack->next && a->last < b->second && \
	are_contiguous(pswap, b->second, a->last))
		sb_move(pswap);
	else if (a->penult < b->first && are_contiguous(pswap, a->penult, b->first))
		rra_move(pswap);
	else if (pswap->stack_b.stack->next && a->penult < b->last && \
	are_contiguous(pswap, a->penult, b->last))
		rrr_move(pswap);
	else
		return (0);
	pa_move(pswap);
	ra_move(pswap);
	return (1);
}

/*
** This function analyses the relative positions of the first number of a and b,
** and nearby numbers (second and last), and if two contiguous numbers are found
** the stacks are rotated as needed to bring the contiguous number in stack a to
** the right position to accept its partner from stack b. I made a bit of an
** ad-hoc function called move and push to accept the appropriate move and do
** push. For the first check no move is needed before the push, so NULL is
** passed instead of a pointer to a move function.
**
** If a condition meriting a move and push is found we return 1, otherwise we
** return 0 to tell the calling function nothing was done.
*/

static int	push_to_stack_a(t_pswap *pswap)
{
	t_stack	*a;
	t_stack	*b;

	get_relevant_numbers(pswap);
	a = &pswap->stack_a;
	b = &pswap->stack_b;
	if (a->first > b->first && are_contiguous(pswap, b->first, a->first))
		move_and_push(NULL, pswap);
	else if (a->first > b->second && are_contiguous(pswap, b->second, a->first))
		move_and_push(sb_move, pswap);
	else if (a->first < b->first && are_contiguous(pswap, a->first, b->first))
		move_and_push(ra_move, pswap);
	else if (a->first > b->last && are_contiguous(pswap, b->last, a->first))
		move_and_push(rrb_move, pswap);
	else if (a->first < b->last && are_contiguous(pswap, a->first, b->last))
		move_and_push(rr_move, pswap);
	else if (a->last > b->first && are_contiguous(pswap, b->first, a->last))
		move_and_push(rra_move, pswap);
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
	static char	stayout = 0;

	if (!stayout)
	{
		i = pswap->numbers - 3;
		while (i--)
			pb_move(pswap);
		while (!stack_a_is_sequenced(pswap, &pswap->stack_a))
			three_numbers(pswap);
		stayout = 1;
	}
	else if (pswap->stack_b.numbers > 0)
	{
		if (!push_to_stack_a(pswap) && !push_to_stack_a_and_rotate(pswap))
			ra_move(pswap);
	}
}

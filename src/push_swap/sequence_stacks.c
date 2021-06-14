/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_stacks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 22:24:55 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/14 22:30:41 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** This function reports whether or not a given pair of integers within a stack
** is sequenced.
**
** A SEQUENCED number pair is any ASCENDING pair of numbers, EXCEPT the smallest
** and largest in the stack. Incidentally, this means that the smallest/largest
** pair is sequenced if it is DESCENDING. :) So, for the stack 1 2 0, 0 and 2
** 0 are sequenced, while for the stack 2 1 0, 1 and 0 are unsequenced.
**
** This distinction is important as sequenced stacks can be rotated into order.

** The first member of the pair to be analysed is passed as the integer anterior
** and the second is passed as the integer posterior.
*/

int	pair_is_sequenced(t_stack *stack, int anterior, int posterior)
{
	if (anterior > posterior && !(anterior == stack->largest && \
	posterior == stack->smallest))
		return (0);
	return (1);
}

/*
** Identifies the next unsequenced pair from the top moving downwards in the
** stack. The distance from the top to the first member of the pair is counted.
** This corresponds to the r-distance, or distance in r-moves from the top. The
** distance in rr-moves is the inverse of the distance in r-moves, given by
** stack->numbers - r-moves.
**
** The r_moves and rr_moves from the next unsequenced pair to the top are saved
** in the struct to which the sequence pointer points. A pointer to the smallest
** of the two is also saved as the shortest path. If both paths are the same
** length, a pointer to NULL is saved. This function assumes there *are*
** unsequenced pairs in the stack and that the stack in question exists so DON'T
** use it unless it is behind a stack_is_sequenced query that returns false. It
** also assumes the sequence structure exists.
*/

void	find_next_unsequenced_pair(t_stack *stack, t_sequence *sequence)
{
	t_list	*stk;
	size_t	i;

	stk = stack->stack;
	i = 0;
	while (stk->next)
	{
		if (!pair_is_sequenced(stack, *(int *)stk->content, \
		*(int *)stk->next->content))
			break ;
		stk = stk->next;
		i++;
	}
	sequence->r_moves = i;
	sequence->rr_moves = stack->numbers - i;
}

/*
** This function uses the last two bits of the seq_flag to identify whether
** stack_a and stack_b are "sequenced". A stack is considered sequenced when
** it is in ascending order except for the transition between the smallest
** and largest number in the stack, considering that stacks loop, so the last
** number in a stack is next to the first number. For example, 1 2 0 is
** sequenced, because all numbers are in ascending order except for 2 (the
** largest) and 0 (the smallest). 1 0 2 is NOT sequenced because this is not
** true. So we separate each number series into the set of sequenced
** combinations and the set of unsequenced combinations.
**
** The algorithmic approach seeks first to sequence and then to order the
** stacks. This is to maximize the possibility of double-swap instructions (ss),
** since sequencing a stack means using swap. If I have to swap numbers in
** stack_a and stack_b, it is more instruction-efficient to bring the numbers I
** want to swap to the top of both stacks and swap them simultaneously with a
** single ss instruction, so this function will try to do that for as long as it
** can. We should sequence with roughly half of all numbers in the series in
** stack_b and the other half in stack_a.
**
** To achieve this we query whether each of the stacks are sequenced and bitwise
** OR both of their results into the seq_flag. The query will return 0 for not
** sequenced and 1 for sequenced. Empty stacks will be considered sequenced and
** return 1.
**
** Thus, the bitwise OR seq_flag values equate to the following information:
**
** Bin	Dec
** 00 == 00 - Neither stack is sequenced
** 01 == 01 - Only stack_a is sequenced
** 10 == 02 - Only stack_b is sequenced
** 11 == 03 - Both stacks are sequenced
**
** After both stacks are sequenced we can now merge_sort Stack_B back into
** Stack_A...
*/

void	sequence_stacks(t_pswap *pswap)
{
	char	seq_flag;

	seq_flag = (char)(stack_a_is_sequenced(pswap, &pswap->stack_a) \
	 | (stack_b_is_sequenced(pswap, &pswap->stack_b) << 1));
	get_relevant_numbers(pswap);
	if (seq_flag == 2 || seq_flag == 0)
		while (pswap->stack_a.numbers > 2)
			push_lowers(pswap);
	while (pswap->stack_b.stack)
		merge_sequence(pswap);
}

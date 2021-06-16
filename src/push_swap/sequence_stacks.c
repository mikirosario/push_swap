/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_stacks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 22:24:55 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/15 21:30:35 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_conditions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 22:05:11 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/08 21:31:07 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Determines whether two numbers are contiguous in the series. The binary tree
** is used for traversal to save time. Equal values are not allowed by the
** program so that should never happen, but just in case I have the program
** throw a conspicuous error if it ever did.
**
** Although int arguments are labelled smaller and larger, the function will
** actually tolerate it if the programmer is naughty and passes the larger
** number as 'smaller' and the 'smaller' as larger - they will just be swapped.
**
** If values are found in the series that are between the two numbers passed as
** arguments, the function returns 0. Otherwise, the values are deemed
** contiguous and the function returns 1.
*/

int	are_contiguous(t_pswap *pswap, int smaller, int larger)
{
	int			tmp;
	t_bstnode	*ret;

	if (smaller == larger)
		exit_failure("are_contiguous function received equal values", pswap);
	if (smaller > larger)
	{
		tmp = smaller;
		smaller = larger;
		larger = tmp;
	}
	if (larger - smaller == 1)
		return (1);
	ret = NULL;
	tmp = smaller + 1;
	while (ret == NULL && tmp < larger)
		ret = ft_bintree_search(pswap->bintree, (long long int)tmp++);
	if (ret == NULL)
		return (1);
	return (0);
}

/*
** This function informs the algorithm whether or not the numbers are ordered.
** Numbers are considered ordered if they are at their desired position. Numbers
** are in their desired position if their position in the position map is 0 (at
** 'zero position').
**
** Each stack, stack_a and stack_b, has an associated position map, called
** mask_a and mask_b, respectively.
**
** If numbers are split between stack_a and stack_b, numbers are considered
** ordered if all numbers in stack_a and stack_b are in their 'zero position',
** that is, that they don't have to be swapped or rotated up and down the stacks
** to be ordered. They may still need to be PUSHED, but they are ordered.
**
** The 'zero positions' take into account the First-In-Last-Out nature of the
** stacks, so positions in stack_a are considered 'displaced' in the negative
** direction (downwards) by the numbers in stack_b. This is because all numbers
** must eventually return to stack_a, so stack_b is treated as a kind of
** temporary continuation of stack_a. Thus, if there are two numbers in stack_b,
** the effective position of the first number in stack_a will be its stack_a
** position minus 2 due to displacement in the negative direction.
**
** In the example below, the desired position of 4 as at the end of the list.
** The 4 is above the end of the list (in the positive direction), so it has
** a positive offset. But the offset is not 4, but rather 2, because it will be
** be displaced downwards (in the negative direction) in stack_a two times by
** numbers pushed over from stack_b.
**
** STACK_A		STACK_B		OFFSET FROM
**							DESIRED POSITION
**	 +			  -
**	 4↓←←←←←←←←←←				 2
**	 1↓ NEGATIVE↑				-2
**	 2↓	  DIR.	↑				-2
**	  ↓		 	↑3				 2
**	  ↓		  	↑0				 0
**	 -			  +
**
** An ordered list with the same distribution would look like this:
**
** STACK_A		STACK_B		OFFSET FROM
**							DESIRED POSITION
**	 +			  -
**	 2↓←←←←←←←←←←				 0
**	 3↓ NEGATIVE↑				 0
**	 4↓	  DIR.	↑				 0
**	  ↓		 	↑1				 0
**	  ↓		  	↑0				 0
**	 -			  +
**
** So, if this function returns true, then all that must be done to sort the
** numbers is to push all remaining numbers in stack_b (if any) to stack_a. Thus
** we request pa_move * numbers_in_stack_b.
**
** Therefore, this function will determine whether numbers are ordered
** regardless of how they are distributed across the stacks. So this is a
** stack-invariant ordering check. Regardless of whether stack_b or stack_a are
** empty, or numbers are distributed between them, the function will detect when
** the numbers are ordered.
**
** This function will interrupt the other sorting algorithms if it detects a
** stack-invariant ordering at any point and simply do pa (if some of the
** ordered numbers are in stack_b) until all numbers are in stack_a. It doesn't
** care if there is no stack_b, so it functions as a general ordering check too.
** It will only return true if *all* numbers are ordered, not just those of one
** or the other stack.
*/

char	is_ordered(t_pswap *pswap)
{
	size_t	i;
	size_t	stack_b_numbers;

	generate_position_map(pswap);
	i = pswap->stack_b.mask.start_index;
	while (i < pswap->numbers)
		if (pswap->stack_b.mask.vector[i++])
			return (0);
	i = pswap->stack_a.mask.start_index;
	while (i < pswap->numbers)
		if (pswap->stack_a.mask.vector[i++])
			return (0);
	i = 0;
	stack_b_numbers = pswap->stack_b.numbers;
	while (i++ < stack_b_numbers)
		pa_move(pswap);
	return (1);
}

/*
** This function will determine whether or not a given series of numbers in
** the stack passed as stack is sequenced, though not necessarily ordered. That
** is, counting from the smallest number (stack->smallest) downward and looping
** around to the top at the end of the stack, all numbers are in sequential
** DESCENDING order. So this is to be used with stack b.
**
** If true, then the sort_rotate function can be used to finalize the sorting.
**
** Two of the relevant numbers we generate are the smallest and largest integers
** in the stack. Except for the transition from the largest to the smallest, we
** require the stack to go in DESCENDING order. If we hit any neighbouring
** numbers in which a number is lesser than the subsequent number, we ask if it
** is true that the number is the smallest in the stack and the subsequent number
** is the largest in the stack. If it is NOT true, we return 0. If the whole
** stack is traversed then we return 1 to indicate that it is sequenced. If the
** stack being queried does not exist them we also return 1, as non-existent
** stacks are considered ordered within program logic.
*/

int	stack_b_is_sequenced(t_pswap *pswap, t_stack *stack)
{
	t_list	*stk;
	size_t	i;
	int		anterior;
	int		posterior;

	get_relevant_numbers(pswap);
	stk = stack->stack;
	i = stack->numbers;
	if (stk == NULL)
		return (1);
	while (i--)
	{
		anterior = *(int *)stk->content;
		if (stk->next == NULL)
			posterior = *(int *)stack->stack->content;
		else
			posterior = *(int *)stk->next->content;
		if (anterior < posterior && \
		!(anterior == stack->smallest && posterior == stack->largest))
			return (0);
		stk = stk->next;
	}
	return (1);
}

/*
** This function will determine whether or not a given series of numbers in
** the stack passed as stack is sequenced, though not necessarily ordered. That
** is, counting from the smallest number (stack->smallest) downward and looping
** around to the top at the end of the stack, all numbers are in sequential
** ASCENDING order. So this is to be used with stack a.
**
** If true, then the sort_rotate function can be used to finalize the sorting.
**
** Two of the relevant numbers we generate are the smallest and largest integers
** in the stack. Except for the transition from the largest to the smallest, we
** require the stack to go in ASCENDING order. If we hit any neighbouring
** numbers in which a number is greater than the subsequent number, we ask if it
** is true that the number is the largest in the stack and the subsequent number
** is the smallest in the stack. If it is NOT true, we return 0. If the whole
** stack is traversed then we return 1 to indicate that it is sequenced. If the
** stack being queried does not exist them we also return 1, as non-existent
** stacks are considered ordered within program logic.
*/

int	stack_a_is_sequenced(t_pswap *pswap, t_stack *stack)
{
	t_list	*stk;
	size_t	i;
	int		anterior;
	int		posterior;

	get_relevant_numbers(pswap);
	stk = stack->stack;
	i = stack->numbers;
	if (stk == NULL)
		return (1);
	while (i--)
	{
		anterior = *(int *)stk->content;
		if (stk->next == NULL)
			posterior = *(int *)stack->stack->content;
		else
			posterior = *(int *)stk->next->content;
		if (anterior > posterior && \
		!(anterior == stack->largest && posterior == stack->smallest))
			return (0);
		stk = stk->next;
	}
	return (1);
}

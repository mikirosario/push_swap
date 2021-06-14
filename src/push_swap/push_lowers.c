/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_lowers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 19:50:56 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/14 22:28:58 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** This function receives a pointer to a range of integers of size array_size
** and checks whether the integer passed as num is in the array. Used to check
** whether a given number at the top of stack_a is part of the declared range.
**
** If num is in the range, 1 is returned. Otherwise 0 is returned.
*/

int	has_num(int *array, size_t array_size, int num)
{
	while (array_size--)
		if (array[array_size] == num)
			return (1);
	return (0);
}

/*
** This function is used by get_range to get the next largest number in the
** stack passed as stack after the number passed as num.
**
** The next number will be the smallest of the set of numbers that are larger
** than num, so that is what the if checks for, a number larger than num and
** smaller than the largest such number found so far, which we save as 'next'.
**
** The variable next is initialized to INT_MAX so any valid number that is not
** INT_MAX will be smaller.
**
** Once the entire stack is traversed, the next number is returned.
*/

int	get_next_num(t_list *stack, int	num)
{
	int	next;

	next = INT_MAX;
	while (stack)
	{
		if ((*(int *)stack->content > num) && *(int *)stack->content <= next)
			next = *(int *)stack->content;
		stack = stack->next;
	}
	return (next);
}

/*
** This function reserves memory for an integer array of size range_size. If an
** array was already created, it is freed first.
**
** The first digit of the array is set to the smallest integer in stack_a. Every
** subsequent integer in the array is set to the next largest integer from the
** last in stack_a until the array is filled. This is the 'range'. To get the
** next largest number in the stack, the get_next_num function is used.
**
** The range_size is set by the program and many different range sizes are
** tested for every number series. If the remaining numbers in stack_a are fewer
** than the range_size, the range_size is set to be equal to the remaining
** remaining numbers.
*/

void	get_range(t_pswap *pswap)
{
	size_t	i;

	i = 0;
	get_relevant_numbers(pswap);
	if (pswap->pivot.range_size > pswap->stack_a.numbers)
		pswap->pivot.range_size = pswap->stack_a.numbers;
	if (pswap->pivot.range)
		pswap->pivot.range = ft_del(pswap->pivot.range);
	pswap->pivot.range = malloc(pswap->pivot.range_size * sizeof(int));
	pswap->pivot.range[i++] = pswap->stack_a.smallest;
	while (i < pswap->pivot.range_size)
	{
		pswap->pivot.range[i] = \
		get_next_num(pswap->stack_a.stack, pswap->pivot.range[i - 1]);
		i++;
	}
}

/*
** This function selects a range of numbers from the lowest in the stack to the
** the highest within the range based on the set range_size. It then checks the
** first number in stack_a against the range of numbers. If the first number in
** stack_a is present in the range, then the number is pushed to stack_b.
**
** If it is not present, then stack_a is rotated to look at the next integer.
**
** If the number at the top of stack_b is smaller than the designated pivot for
** stack_b, it is pushed to the bottom of the stack_b. The pivot for stack_b is
** is always the median of the range. Hence, in every group of numbers, the
** smaller ones go to the bottom of stack_b and the larger ones go to the top.
**
** As the range progressively refers to higher and higher integers, stack_b
** becomes a bit like an onion, with the smallest numbers in the middle, and
** the largest numbers at the extremes. This leaves it 'pre-ordered'. Since
** to order stack_a the largest numbers need to be pushed first, less rotates
** will be needed to access them as the numbers that need to be pushed will
** always tend to be close to the top.
**
** For every range we go through all of stack_a until all numbers in the range
** are pushed. Thus, stack_a becomes progressively smaller by range_size
** integers every iteration. If stack_a becomes smaller than the range_size,
** get_range will declare all remaining numbers in stack_a to be part of the
** range.
*
** The largest number is never pushed to stack_b as it would only need to be
** pushed back.
*/

void	push_lowers(t_pswap *pswap)
{
	t_list			*stack_a;
	size_t			i;

	get_range(pswap);
	pswap->pivot.pivot_b = \
	pswap->pivot.range[(pswap->pivot.range_size - 1) / 2];
	i = pswap->stack_a.numbers;
	stack_a = pswap->stack_a.stack;
	while (i--)
	{
		if (*(int *)stack_a->content != pswap->largest && \
		has_num(pswap->pivot.range, pswap->pivot.range_size, \
		*(int *)stack_a->content))
			pb_move(pswap);
		else
			ra_move(pswap);
		get_relevant_numbers(pswap);
		if (pswap->stack_b.first < pswap->pivot.pivot_b)
			rb_move(pswap);
		stack_a = pswap->stack_a.stack;
	}
}

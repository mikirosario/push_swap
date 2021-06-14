/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_relevant_numbers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 04:43:06 by miki              #+#    #+#             */
/*   Updated: 2021/06/14 16:42:14 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	get_extremes(t_pswap *pswap, t_list *stack)
{
	t_list		*extremes;
	int			*smallest;
	int			*largest;

	if (stack == pswap->stack_a.stack)
	{
		smallest = &pswap->stack_a.smallest;
		largest = &pswap->stack_a.largest;
	}
	else
	{
		smallest = &pswap->stack_b.smallest;
		largest = &pswap->stack_b.largest;
	}
	extremes = stack;
	while (extremes)
	{
		if (*smallest > *(int *)extremes->content)
			*smallest = *(int *)extremes->content;
		if (*largest < *(int *)extremes->content)
			*largest = *(int *)extremes->content;
		extremes = extremes->next;
	}
}

void	get_relevant_stack_b_numbers(t_pswap *pswap)
{
	t_list		*penult_b;

	penult_b = pswap->stack_b.stack;
	pswap->stack_b.smallest = INT_MAX;
	pswap->stack_b.largest = INT_MIN;
	get_extremes(pswap, pswap->stack_b.stack);
	while (penult_b->next && penult_b->next->next)
		penult_b = penult_b->next;
	pswap->stack_b.first = *(int *)pswap->stack_b.stack->content;
	if (pswap->stack_b.stack->next)
		pswap->stack_b.second = *(int *)pswap->stack_b.stack->next->content;
	else
		pswap->stack_b.second = pswap->stack_b.first;
	pswap->stack_b.penult = *(int *)penult_b->content;
	pswap->stack_b.last = *(int *)(ft_lstlast(pswap->stack_b.stack))->content;
}

void	get_relevant_stack_a_numbers(t_pswap *pswap)
{
	t_list		*penult_a;

	penult_a = pswap->stack_a.stack;
	pswap->stack_a.smallest = INT_MAX;
	pswap->stack_a.largest = INT_MIN;
	get_extremes(pswap, pswap->stack_a.stack);
	while (penult_a->next && penult_a->next->next)
		penult_a = penult_a->next;
	pswap->stack_a.first = *(int *)pswap->stack_a.stack->content;
	if (pswap->stack_a.stack->next)
		pswap->stack_a.second = *(int *)pswap->stack_a.stack->next->content;
	else
		pswap->stack_a.second = pswap->stack_a.first;
	pswap->stack_a.penult = *(int *)penult_a->content;
	pswap->stack_a.last = *(int *)(ft_lstlast(pswap->stack_a.stack))->content;
}

/*
** The 'relevant numbers' are those that can be directly affected by the next
** two moves, not including any pushes that may be needed to send numbers
** between stacks.
**
** These are the first, second, penultimate and last numbers of stack_a and
** stack_b. For stacks smaller than 4, the penultimate will be the same as the
** second. For stacks smaller than 3 the last will be the same as the second.
** For stacks of size 1, all relevant numbers will be equal to the only number
** in the stack. No attempt should be made to get relevant numbers for stacks
** that do not exist, it will not work, and behaviour will be 'undefined',
** but expect bedlam. :p
*/

void	get_relevant_numbers(t_pswap *pswap)
{
	if (pswap->stack_a.stack)
		get_relevant_stack_a_numbers(pswap);
	if (pswap->stack_b.stack)
		get_relevant_stack_b_numbers(pswap);
}

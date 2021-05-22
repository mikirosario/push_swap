/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_conditions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 22:05:11 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/21 19:33:45 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** This function informs the algorithm whether or not the numbers are ordered.
** Numbers are considered ordered if they are at their desired position. Numbers
** in stack_b are in their desired position if their position in mask_b is zero.
**
** If numbers are split between stack_a and stack_b, numbers are considered
** ordered if all numbers in stack_a and stack_b are in their 'zero position',
** that is, that they don't have to be moved up or down the stacks to be
** ordered. The 'zero positions' take into account the First-In-Last-Out nature
** of the stacks, so positions in stack_a are considered 'displaced' by
** numbers_in_stack_b places in the negative direction (downwards).
**
** So, if this function returns true, then all that must be done to order the
** numbers is to pass all remaining numbers in stack_b (if any) to stack_a. Thus
** we request pa_move * numbers_in_stack_b.
**
** If all numbers are in stack_a then numbers_in_stack_b == 0, so all numbers in
** stack_a must be at their zero position to be considered ordered. If all
** numbers are in stack_b then numbers_in_stack_a == 0, all stack_b numbers must
** be in their zero position to be considered ordered. Then they are all passed
** back to stack_a.
**
** Therefore, this function will determine whether numbers are ordered
** regardless of how they are distributed across the stacks. So this is a
** distribution-independent ordering check.
*/

char	is_ordered(t_pswap *pswap)
{
	//t_list	*tmp;
	//size_t	numbers_in_stack_b;
	//size_t	numbers_in_stack_a;
	size_t	i;

	//NUMBERS IN STACK_B
	// tmp = pswap->stack_b;
	// numbers_in_stack_b = 0;
	// while (tmp)
	// {
	// 	numbers_in_stack_b++;
	// 	tmp = tmp->next;
	// }
	//ALL MASK_B POSITION NUMBERS ARE AT ZERO POSITION
	i = pswap->mask_b.start_index;
	while (i < pswap->numbers)
		if (pswap->mask_b.vector[i++])
			return (0);
	//NUMBERS IN STACK_A
	// tmp = pswap->stack_a;
	// numbers_in_stack_a = 0;
	// while (tmp)
	// {
	// 	numbers_in_stack_a++;
	// 	tmp = tmp->next;
	// }
	//ALL MASK_A POSITION NUMBERS ARE AT ZERO POSITION
	i = pswap->mask_a.start_index;
	while (i < pswap->numbers)
		if (pswap->mask_a.vector[i++])
			return (0);
	//ADD PA * NUMBERS_IN_STACK_B MOVEMENTS
	i = 0;
	while (i++ < pswap->stack_b_numbers)
		pa_move(pswap);
return (1);
}
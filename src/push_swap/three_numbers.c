/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:55:51 by miki              #+#    #+#             */
/*   Updated: 2021/05/25 23:33:06 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// static int	rra_case(t_pswap *pswap)
// {
// 	t_stack *stack_a;

// 	stack_a = &pswap->num;
// 	get_relevant_numbers(pswap);
// 	if (stack_a->second == stack_a->largest && stack_a->last == stack_a->smallest)
// 		return (1);
// 	return (0);
// }

// static int	ra_case(t_pswap *pswap)
// {
// 	t_stack *stack_a;

// 	stack_a = &pswap->num;
// 	get_relevant_numbers(pswap);
// 	if (stack_a->first == stack_a->largest
// 	 && (stack_a->second == stack_a->smallest || stack_a->last == stack_a->smallest))
// 		return (1);
// 	return (0);
// }

// static int	sa_case(t_pswap	*pswap)
// {
// 	t_stack *stack_a;

// 	stack_a = &pswap->num;
// 	get_relevant_numbers(pswap);
// 	if ((stack_a->first == stack_a->smallest && stack_a->second == stack_a->largest)
// 	 || (stack_a->last == stack_a->largest && stack_a->second == stack_a->smallest))
// 		return (1);
// 	return (0);
// }

/*
** This algorithm sequences all cases from 1 to 3 numbers. This means it leaves
** the series in a sequence, that is, starting from the lowest number and moving
** down the series, looping back to the top at the end, all numbers are in
** ascending order, though they are not yet sorted. For all numbers from 1 to 3
** this can be achieved with just one move - sa.
*/

void	three_numbers(t_pswap *pswap)
{
	t_stack	*stack_a;

	stack_a = &pswap->num_a;
	get_relevant_numbers(pswap);
	if ((stack_a->first == stack_a->smallest && stack_a->second == stack_a->largest)
	 || (stack_a->last == stack_a->largest && stack_a->second == stack_a->smallest)
	 || (stack_a->first == stack_a->largest && stack_a->last == stack_a->smallest))
		sa_move(pswap);
generate_position_map(pswap);
	// if (sa_case(pswap))
	// 	sa_move(pswap);
	// else if (ra_case(pswap))
	// 	ra_move(pswap);
	// else
	// 	rra_move(pswap);
	//debug code
	//printf("STACK A SMALLEST: %d STACK A LARGEST: %d\n", pswap->num_a.smallest, pswap->num_a.largest);
}

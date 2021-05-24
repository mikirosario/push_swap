/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:55:51 by miki              #+#    #+#             */
/*   Updated: 2021/05/24 02:43:21 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// static int	rra_case(t_pswap *pswap)
// {
// 	t_relevant	*n;

// 	n = &pswap->num;
// 	get_relevant_numbers(pswap);
// 	if (n->a_second == n->largest && n->a_last == n->a_smallest)
// 		return (1);
// 	return (0);
// }

// static int	ra_case(t_pswap *pswap)
// {
// 	t_relevant	*n;

// 	n = &pswap->num;
// 	get_relevant_numbers(pswap);
// 	if (n->a_first == n->a_largest
// 	 && (n->a_second == n->a_smallest || n->a_last == n->a_smallest))
// 		return (1);
// 	return (0);
// }

// static int	sa_case(t_pswap	*pswap)
// {
// 	t_relevant	*n;

// 	n = &pswap->num;
// 	get_relevant_numbers(pswap);
// 	if ((n->a_first == n->a_smallest && n->a_second == n->a_largest)
// 	 || (n->a_last == n->a_largest && n->a_second == n->a_smallest))
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
	t_relevant	*n;

	n = &pswap->num;
	get_relevant_numbers(pswap);
	if ((n->a_first == n->a_smallest && n->a_second == n->a_largest)
	 || (n->a_last == n->a_largest && n->a_second == n->a_smallest)
	 || (n->a_first == n->a_largest && n->a_last == n->a_smallest))
		sa_move(pswap);
generate_position_map(pswap);
	// if (sa_case(pswap))
	// 	sa_move(pswap);
	// else if (ra_case(pswap))
	// 	ra_move(pswap);
	// else
	// 	rra_move(pswap);
	//debug code
	//printf("STACK A SMALLEST: %d STACK A LARGEST: %d\n", pswap->num.a_smallest, pswap->num.a_largest);
}

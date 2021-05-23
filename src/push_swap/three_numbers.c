/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:55:51 by miki              #+#    #+#             */
/*   Updated: 2021/05/23 23:54:53 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	rra_case(t_pswap *pswap)
{
	t_relevant	*n;

	n = &pswap->num;
	get_relevant_numbers(pswap);
	if (n->a_second == n->largest && n->a_last == n->a_smallest)
		return (1);
	return (0);
}

static int	ra_case(t_pswap *pswap)
{
	t_relevant	*n;

	n = &pswap->num;
	get_relevant_numbers(pswap);
	if (n->a_first == n->a_largest)
		return (1);
	return (0);
}

static int	sa_case(t_pswap	*pswap)
{
	t_relevant	*n;

	n = &pswap->num;
	get_relevant_numbers(pswap);
	if (n->a_last == n->a_largest || (n->a_second == n->a_largest && n->a_first == n->a_smallest))
		return (1);
	return (0);
}

/*
** This algorithm handles all cases from 1 to 3 numbers.
*/

void	three_numbers(t_pswap *pswap)
{
	generate_position_map(pswap);
	if (sa_case(pswap))
		sa_move(pswap);
	else if (ra_case(pswap))
		ra_move(pswap);
	else if (rra_case(pswap))
		rra_move(pswap);
	//debug code
	printf("STACK A SMALLEST: %d STACK A LARGEST: %d\n", pswap->num.a_smallest, pswap->num.a_largest);
}

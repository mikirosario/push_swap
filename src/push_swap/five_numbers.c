/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   five_numbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:18:16 by miki              #+#    #+#             */
/*   Updated: 2021/05/21 22:19:41 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** This algorithm handles 4 and 5 numbers.
*/

void	five_numbers(t_pswap *pswap)
{
	size_t		i;
	static char		stayout = 0;

	if (!stayout)
	{
		i = pswap->numbers - 3;
		while (i--)
			pb_move(pswap);
		stayout = 1;
	}
	else if (pswap->stack_a_numbers > 3)
	{
		if (should_swap_stack_a(pswap))
			sa_move(pswap);
		else if (should_rotate_stack_a(pswap))
			rotate_stack(pswap, pswap->stack_a);
		else
		{
			ra_move(pswap);
			pb_move(pswap);
		}
	}
	else if (!is_sorted(pswap->stack_a))
		three_numbers(pswap);
	else if (pswap->stack_b)
		pa_move(pswap);
}

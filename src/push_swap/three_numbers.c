/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:55:51 by miki              #+#    #+#             */
/*   Updated: 2021/05/20 16:45:43 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	rra_case(t_pswap *pswap)
{
	if (pswap->mask_a.vector[0] == 1 && pswap->mask_a.vector[1] == 1
	 && pswap->mask_a.vector[2] == -2)
	 	return (1);
	return (0);
}

static int	ra_case(t_pswap *pswap)
{
	if (pswap->mask_a.vector[0] == 2 && ((pswap->mask_a.vector[1] == -1 \
	 && pswap->mask_a.vector[2] == -1) || (pswap->mask_a.vector[1] == 0 \
	 && pswap->mask_a.vector[2] == -2)))
	 	return (1);
	return (0);
}

static int	sa_case(t_pswap	*pswap)
{
	if ((pswap->mask_a.vector[0] == 0 && pswap->mask_a.vector[1] == 1 \
	 && pswap->mask_a.vector[2] == -1) || (pswap->mask_a.vector[0] == 1 \
	 && pswap->mask_a.vector[1] == -1 && pswap->mask_a.vector[2] == 0))
	 	return (1);
	return (0);
}

void	three_numbers(t_pswap *pswap)
{
	if (sa_case(pswap))
		sa_move(pswap);
	else if (ra_case(pswap))
		ra_move(pswap);
	else if (rra_case(pswap))
		rra_move(pswap);
}
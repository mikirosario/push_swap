/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:55:51 by miki              #+#    #+#             */
/*   Updated: 2021/05/21 18:43:30 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	rra_case(t_pswap *pswap)
{
	int		*mask_a;
	size_t	i;

	mask_a = pswap->mask_a.vector;
	i = pswap->mask_a.start_index;
	if (mask_a[i] == mask_a[i + 1] && mask_a[i + 1] > mask_a[i + 2])
		return (1);
	return (0);
}

static int	ra_case(t_pswap *pswap)
{
	int		*mask_a;
	size_t	i;

	mask_a = pswap->mask_a.vector;
	i = pswap->mask_a.start_index;
	if (mask_a[i] > mask_a[i + 1] && mask_a[i + 1] >= mask_a[i + 2])
		return (1);
	return (0);
}

static int	sa_case(t_pswap	*pswap)
{
	int		*mask_a;
	size_t	i;

	mask_a = pswap->mask_a.vector;
	i = pswap->mask_a.start_index;
	if ((mask_a[i] < mask_a[i + 1] && mask_a[i + 1] > mask_a[i + 2]) \
	 || (mask_a[i] > mask_a[i + 1] && mask_a[i + 1] < mask_a[i + 2]))
	 	return (1);
	return (0);
}

/*
** This algorithm handles all cases from 1 to 3 numbers.
*/

void	three_numbers(t_pswap *pswap)
{
	if (sa_case(pswap))
		sa_move(pswap);
	else if (ra_case(pswap))
		ra_move(pswap);
	else if (rra_case(pswap))
		rra_move(pswap);
}
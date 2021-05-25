/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_stacks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 22:24:55 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/25 23:16:34 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sequence_stacks(t_pswap *pswap)
{
	char	stack_a_sequenced;
	char	stack_b_sequenced;

	stack_a_sequenced = stack_a_is_sequenced(pswap);
	stack_b_sequenced = stack_b_is_sequenced(pswap);
	if (pswap->stack_a && pswap->stack_b)
}

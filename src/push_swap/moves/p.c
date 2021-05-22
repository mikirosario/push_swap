/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:11:38 by miki              #+#    #+#             */
/*   Updated: 2021/05/21 19:36:29 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** This function makes the first member of stack b into the first member of
** stack a, and the second member of stack b into the first member of stack b.
*/

void	pa_move(t_pswap *pswap)
{
	t_list	*bring_to_front;

	if (!pswap->stack_b)
		return ;
	bring_to_front = pswap->stack_b->next;
	ft_lstadd_front(&pswap->stack_a, pswap->stack_b);
	pswap->stack_b = bring_to_front;
	pswap->stack_a_numbers++;
	pswap->stack_b_numbers--;
	pswap->mask_a.start_index = pswap->stack_b_numbers;
	pswap->mask_b.start_index = pswap->stack_a_numbers;
	add_move_to_list(pswap, "pa");
}

/*
** This function makes the first member of stack a into the first member of
** stack b, and the second member of stack a into the first member of stack a.
*/

void	pb_move(t_pswap *pswap)
{
	t_list	*bring_to_front;

	if (!pswap->stack_a)
		return ;
	bring_to_front = pswap->stack_a->next;
	ft_lstadd_front(&pswap->stack_b, pswap->stack_a);
	pswap->stack_a = bring_to_front;
	pswap->stack_b_numbers++;
	pswap->stack_a_numbers--;
	pswap->mask_a.start_index = pswap->stack_b_numbers;
	pswap->mask_b.start_index = pswap->stack_a_numbers;
	add_move_to_list(pswap, "pb");
}

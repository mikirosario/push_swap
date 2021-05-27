/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:11:38 by miki              #+#    #+#             */
/*   Updated: 2021/05/27 12:55:59 by miki             ###   ########.fr       */
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

	if (!pswap->stack_b.stack)
		return ;
	bring_to_front = pswap->stack_b.stack->next;
	ft_lstadd_front(&pswap->stack_a.stack, pswap->stack_b.stack);
	pswap->stack_b.stack = bring_to_front;
	pswap->stack_a.numbers++;
	pswap->stack_b.numbers--;
	pswap->stack_a.mask.start_index--;
	pswap->stack_b.mask.start_index++;
	add_move_to_list(pswap, "pa");
}

/*
** This function makes the first member of stack a into the first member of
** stack b, and the second member of stack a into the first member of stack a.
*/

void	pb_move(t_pswap *pswap)
{
	t_list	*bring_to_front;

	if (!pswap->stack_a.stack)
		return ;
	bring_to_front = pswap->stack_a.stack->next;
	ft_lstadd_front(&pswap->stack_b.stack, pswap->stack_a.stack);
	pswap->stack_a.stack = bring_to_front;
	pswap->stack_b.numbers++;
	pswap->stack_a.numbers--;
	pswap->stack_a.mask.start_index++;
	pswap->stack_b.mask.start_index--;
	add_move_to_list(pswap, "pb");
}

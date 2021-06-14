/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 21:49:13 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/14 21:30:52 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sb_move(t_pswap *pswap)
{
	int	tmp;

	if (!pswap->stack_b.stack || !pswap->stack_b.stack->next)
		return ;
	tmp = *(int *)pswap->stack_b.stack->next->content;
	*(int *)pswap->stack_b.stack->next->content = \
	*(int *)pswap->stack_b.stack->content;
	*(int *)pswap->stack_b.stack->content = tmp;
	add_move_to_list(pswap, "sb");
}

void	sa_move(t_pswap *pswap)
{
	int	tmp;

	if (!pswap->stack_a.stack || !pswap->stack_a.stack->next)
		return ;
	tmp = *(int *)pswap->stack_a.stack->next->content;
	*(int *)pswap->stack_a.stack->next->content = \
	*(int *)pswap->stack_a.stack->content;
	*(int *)pswap->stack_a.stack->content = tmp;
	add_move_to_list(pswap, "sa");
}

void	ss_move(t_pswap *pswap)
{
	sa_move(pswap);
	sb_move(pswap);
}

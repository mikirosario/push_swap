/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 21:49:13 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/16 23:16:49 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sb_move(t_pswap *pswap)
{
	int tmp;

	if (!pswap->stack_b || !pswap->stack_b->next)
		return ;
	tmp = *(int *)pswap->stack_b->next->content;
	*(int *)pswap->stack_b->next->content = *(int *)pswap->stack_b->content;
	*(int *)pswap->stack_b->content = tmp;
}

void	sa_move(t_pswap *pswap)
{
	int tmp;

	if (!pswap->stack_a || !pswap->stack_a->next)
		return ;
	tmp = *(int *)pswap->stack_a->next->content;
	*(int *)pswap->stack_a->next->content = *(int *)pswap->stack_a->content;
	*(int *)pswap->stack_a->content = tmp;
}

void	ss_move(t_pswap *pswap)
{
	sa_move(pswap);
	sb_move(pswap);
}

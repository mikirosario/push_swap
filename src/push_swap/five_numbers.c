/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   five_numbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:18:16 by miki              #+#    #+#             */
/*   Updated: 2021/05/22 23:42:07 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


static void	init(t_pswap *pswap)
{
	t_list *penult_a;
	t_list *penult_b;

	penult_a = pswap->stack_a;
	while (penult_a->next && penult_a->next->next)
		penult_a = penult_a->next;
	penult_b = pswap->stack_b;
	while (penult_b->next && penult_b->next->next)
		penult_b = penult_b->next;
	pswap->num.a_first = *(int *)pswap->stack_a->content;
	pswap->num.a_second = *(int *)pswap->stack_a->next->content;
	pswap->num.a_penult = *(int *)penult_a->content;
	pswap->num.a_last = *(int *)(ft_lstlast(pswap->stack_a))->content;
	pswap->num.b_first = *(int *)pswap->stack_b->content;
	if (pswap->stack_b->next)
		pswap->num.b_second = *(int *)pswap->stack_b->next->content;
	pswap->num.b_penult = *(int *)penult_b->content;
	pswap->num.b_last = *(int *)(ft_lstlast(pswap->stack_b))->content;
}

int	push_to_stack_a(t_pswap *pswap)
{
	t_relevant *n;

	init(pswap);
	n = &pswap->num;
	if (n->a_first > n->b_first && are_contiguous(pswap, n->b_first, n->a_first))
		pa_move(pswap);
	else if (n->a_first < n->b_first && are_contiguous(pswap, n->a_first, n->b_first))
	{
		ra_move(pswap);
		pa_move(pswap);
	}
	else if (n->a_first < n->b_last && are_contiguous(pswap, n->a_first, n->b_last))
	{
		rr_move(pswap);
		pa_move(pswap);
	}
	else if (n->a_last > n->b_first && are_contiguous(pswap, n->b_first, n->a_last))
	{
		rra_move(pswap);
		pa_move(pswap);
	}
	else if (pswap->stack_b->next && n->a_last < n->b_second && are_contiguous(pswap, n->b_second, n->a_last))
	{
		sb_move(pswap);
		pa_move(pswap);
		ra_move(pswap);
	}
	else if (n->a_penult < n->b_first && are_contiguous(pswap, n->a_penult, n->b_first))
	{
		rra_move(pswap);
		pa_move(pswap);
		ra_move(pswap);
	}
	else if (pswap->stack_b->next && n->a_penult < n->b_last && are_contiguous(pswap, n->a_penult, n->b_last))
	{
		rrr_move(pswap);
		pa_move(pswap);
		ra_move(pswap);
	}
	else
		return (0);
	return (1);
}

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
		while (!is_sorted(pswap->stack_a))
			three_numbers(pswap);
		stayout = 1;
	}
	else if (pswap->stack_b_numbers > 0)
	{
		if (!push_to_stack_a(pswap))
			ra_move(pswap);
	}
	else if (!is_sorted(pswap->stack_a))
		ra_move(pswap);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rr.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 17:56:17 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/27 12:51:20 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** This function finds the member in the lst pointed to by *lst that comes
** before the list member passed as *member. If there is no such member in the
** list, NULL is returned (assuming the list is properly NULL-terminated,
** naturally).
*/

static t_list	*find_preceding_member(t_list *lst, t_list *member)
{
	if (lst == member)
		return (NULL);
	while (lst && lst->next != member)
		lst = lst->next;
	return (lst);
}

/*
** This function moves the last member of stack_a to the front of the stack,
** making the penultimate member the new last member. If the stack has less than
** two members, nothing is done.
*/

void	rra_move(t_pswap *pswap)
{
	t_list	*last_member;

	if (!pswap->stack_a.stack || !pswap->stack_a.stack->next)
		return ;
	last_member = ft_lstlast(pswap->stack_a.stack);
	(find_preceding_member(pswap->stack_a.stack, last_member))->next = NULL;
	ft_lstadd_front(&pswap->stack_a.stack, last_member);
	add_move_to_list(pswap, "rra");
}

/*
** This function is the same as rra_move, but for stack_b.
*/

void	rrb_move(t_pswap *pswap)
{
	t_list	*last_member;

	if (!pswap->stack_b.stack || !pswap->stack_b.stack->next)
		return ;
	last_member = ft_lstlast(pswap->stack_b.stack);
	(find_preceding_member(pswap->stack_b.stack, last_member))->next = NULL;
	ft_lstadd_front(&pswap->stack_b.stack, last_member);
	add_move_to_list(pswap, "rrb");
}

void	rrr_move(t_pswap *pswap)
{
	rra_move(pswap);
	rrb_move(pswap);
	add_move_to_list(pswap, "rrr");
}

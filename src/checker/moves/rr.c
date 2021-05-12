/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rr.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 17:56:17 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/12 19:16:49 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/*
** This function finds the member in the lst pointed to by *lst that comes
** the list member passed as *member. If there is no such member in the list,
** NULL is returned (assuming the list is properly NULL-terminated, naturally).
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

void	rra_move(t_checker *checker)
{
	t_list	*last_member;

	if (!checker->stack_a || !checker->stack_a->next)
		return ;
	last_member = ft_lstlast(checker->stack_a);
	(find_preceding_member(checker->stack_a, last_member))->next = NULL;
	ft_lstadd_front(&checker->stack_a, last_member);
}

/*
** This function is the same as rra_move, but for stack_b.
*/

void	rrb_move(t_checker *checker)
{
	t_list	*last_member;

	if (!checker->stack_b || !checker->stack_b->next)
		return ;
	last_member = ft_lstlast(checker->stack_b);
	(find_preceding_member(checker->stack_b, last_member))->next = NULL;
	ft_lstadd_front(&checker->stack_b, last_member);
}

void	rrr_move(t_checker *checker)
{
	rra_move(checker);
	rrb_move(checker);
}

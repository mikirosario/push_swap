/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:49:50 by miki              #+#    #+#             */
/*   Updated: 2021/05/10 20:31:09 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/*
** This function moves the first member of stack a to the back and the last
** member to the front. If stack a has less than two members, nothing is done.
**
** The function ft_lst_addfront moves the last member to the front by making
** its next pointer point to the old first member. Then we iterate through the
** list until we find the member whose next pointer points to the old last
** member, and we set it to NULL, as this is now the new last member.
** 
** If only two members are in the list, this is all we do.
**
** If more than two members are in the list (checker->stack_a->next->next), then
** we also set the new first member's next pointer to point to the member after
** the second member, as the new second member is the old first member, which we
** will now be sending to the back. Then we send the old first member to the
** back using ft_lstadd_back. This MUST be done in this order because of how
** my ft_lstadd_back works internally.
*/

void	ra_move(t_checker *checker)
{
	t_list	*last_member;
	t_list	*first_member;
	t_list	*tmp;

	if (!checker->stack_a || !checker->stack_a->next)
		return ;
	last_member = ft_lstlast(checker->stack_a);
	first_member = checker->stack_a;
	tmp = checker->stack_a;
	ft_lstadd_front(&checker->stack_a, last_member);
	while (tmp->next != last_member)
		tmp = tmp->next;
	tmp->next = NULL;
	tmp = checker->stack_a->next->next;
	if (tmp)
	{
		checker->stack_a->next = tmp;
		ft_lstadd_back(&checker->stack_a, first_member);
	}
}

/*
** This function is the same as ra_move, but with stack b.
*/

void	rb_move(t_checker *checker)
{
	t_list	*last_member;
	t_list	*first_member;
	t_list	*tmp;

	if (!checker->stack_b || !checker->stack_b->next)
		return ;
	last_member = ft_lstlast(checker->stack_b);
	first_member = checker->stack_b;
	tmp = checker->stack_b;
	ft_lstadd_front(&checker->stack_b, last_member);
	while (tmp->next != last_member)
		tmp = tmp->next;
	tmp->next = NULL;
	tmp = checker->stack_b->next->next;
	if (tmp)
	{
		checker->stack_b->next = tmp;
		ft_lstadd_back(&checker->stack_b, first_member);
	}
}

void	rr_move(t_checker *checker)
{
	ra_move(checker);
	rb_move(checker);
}

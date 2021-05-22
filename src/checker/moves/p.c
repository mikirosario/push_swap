/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:11:38 by miki              #+#    #+#             */
/*   Updated: 2021/05/21 19:22:59 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/*
** This function makes the first member of stack b into the first member of
** stack a, and the second member of stack b into the first member of stack b.
*/

void	pa_move(t_checker *checker)
{
	t_list	*bring_to_front;

	if (!checker->stack_b)
		return ;
	bring_to_front = checker->stack_b->next;
	ft_lstadd_front(&checker->stack_a, checker->stack_b);
	checker->stack_b = bring_to_front;
}

/*
** This function makes the first member of stack a into the first member of
** stack b, and the second member of stack a into the first member of stack a.
*/

void	pb_move(t_checker *checker)
{
	t_list	*bring_to_front;

	if (!checker->stack_a)
		return ;
	bring_to_front = checker->stack_a->next;
	ft_lstadd_front(&checker->stack_b, checker->stack_a);
	checker->stack_a = bring_to_front;
}

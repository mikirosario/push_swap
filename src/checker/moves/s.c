/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 21:49:13 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/10 17:45:43 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	sb_move(t_checker *checker)
{
	int tmp;

	if (!checker->stack_b || !checker->stack_b->next)
		return ;
	tmp = *(int *)checker->stack_b->next->content;
	*(int *)checker->stack_b->next->content = *(int *)checker->stack_b->content;
	*(int *)checker->stack_b->content = tmp;
}

void	sa_move(t_checker *checker)
{
	int tmp;

	if (!checker->stack_a || !checker->stack_a->next)
		return ;
	tmp = *(int *)checker->stack_a->next->content;
	*(int *)checker->stack_a->next->content = *(int *)checker->stack_a->content;
	*(int *)checker->stack_a->content = tmp;
}

void	ss_move(t_checker *checker)
{
	sa_move(checker);
	sb_move(checker);
}

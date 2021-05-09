/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 21:49:13 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/09 21:51:44 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	sa_move(t_checker *checker)
{
	int	tmp;

	if (!checker->stack_a[0] || !checker->stack_a[1])
		return ;
	tmp = *checker->stack_a[1];
	*checker->stack_a[1] = *checker->stack_a[0];
	*checker->stack_a[0] = tmp;
}

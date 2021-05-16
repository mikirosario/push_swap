/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_conditions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 22:05:11 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/16 23:00:54 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** This function informs the algorithm whether or not the numbers are ordered.
** Numbers are considered ordered if they are at their desired position. Numbers
** in stack_b are in their desired position if their position in mask_b is zero.
**
** If numbers are split between stack_a and stack_b, numbers are considered
** ordered if all numbers in stack_b are in position zero and the difference
** between the actual position of each number in stack_a is equal to the number
** of numbers in stack_b. This is because when ordered stack_b numbers are
** passed to stack_a they will not lose their position, while stack_a numbers
** will be displaced in the positive direction by numbers_in_stack_b times. So,
** in that case all that must be done to order the numbers is to pass all
** remaining numbers in stack_b to stack_b (pa * numbers_in_stack_b).
**
** If all numbers are in stack_a then numbers_in_stack_b == 0, so all numbers in
** stack_a must be at their zero position. If all numbers are in stack_b then
** numbers_in_stack_a == 0, so no comparison is made between stack_a positions
** and the number of numbers in stack_b, rather, all stack_b numbers must simply
** be in their zero position to be considered ordered. Then they are all passed
** back to stack_a.
*/

char	is_ordered(t_pswap *pswap)
{
	t_list	*tmp;
	size_t	numbers_in_stack_b;
	size_t	numbers_in_stack_a;
	size_t	i;

	//NUMBERS IN STACK_B
	tmp = pswap->stack_b;
	numbers_in_stack_b = 0;
	while (tmp)
	{
		numbers_in_stack_b++;
		tmp = tmp->next;
	}
	//ALL MASK_B POSITION NUMBERS ARE ZERO
	i = 0;
	while (i < numbers_in_stack_b)
		if (pswap->mask_b[i++])
			return (0);
	//NUMBERS IN STACK_A
	tmp = pswap->stack_a;
	numbers_in_stack_a = 0;
	while (tmp)
	{
		numbers_in_stack_a++;
		tmp = tmp->next;
	}
	//ALL MASK_A POSITION NUMBERS ARE EQUAL TO NUMBER OF NUMBERS IN STACK_B
	//IF THERE ARE NO NUMBERS IN STACK_B, THIS WILL BE ZERO; SO ALL STACK_A NUMBERS MUST BE AT THEIR ZERO POSITION
	i = 0;
	while (i < numbers_in_stack_a)
		if (pswap->mask_a[i++] != (int)numbers_in_stack_b)
			return (0);
	//ADD PA * NUMBERS_IN_STACK_B MOVEMENTS
	i = 0;
	while (i++ < numbers_in_stack_b)
	{
		tmp = ft_lstnew(ft_strdup("pa"));
		if (!pswap->lst)
			pswap->lst = tmp;
		else
			ft_lstadd_back(&pswap->lst, tmp);
	}
return (1);
}
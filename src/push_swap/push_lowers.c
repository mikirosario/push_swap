/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pivot_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 19:50:56 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/01 23:49:01 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	has_num(int *array, size_t array_size, int num)
{
	while (array_size--)
		if (array[array_size] == num)
			return (1);
	return (0);
}

int	get_next_num(t_list *stack, int	num)
{
	int	next;

	next = INT_MAX;
	while (stack)
	{
		if ((*(int *)stack->content > num) && *(int *)stack->content <= next)
			next = *(int *)stack->content;
		stack = stack->next;
	}
	return (next);
}

void	get_range(t_pswap *pswap)
{
	size_t	i;

	i = 0;
	get_relevant_numbers(pswap);
	if (pswap->pivot.range_size > pswap->stack_a.numbers)
		pswap->pivot.range_size = pswap->stack_a.numbers;
	if (pswap->pivot.range)
		pswap->pivot.range = ft_del(pswap->pivot.range);
	pswap->pivot.range = malloc(pswap->pivot.range_size * sizeof(int));


	//menor de los mayores
	pswap->pivot.range[i++] = pswap->stack_a.smallest;
	while (i < pswap->pivot.range_size)
	{
		pswap->pivot.range[i] = get_next_num(pswap->stack_a.stack, pswap->pivot.range[i - 1]);
		i++;
	}
}

void	push_lowers(t_pswap *pswap)
{
	t_list			*stack_a;

	get_range(pswap);
	stack_a = pswap->stack_a.stack;
	if (*(int *)stack_a->content != pswap->largest && has_num(pswap->pivot.range, pswap->pivot.range_size, *(int *)stack_a->content))
		pb_move(pswap);
	else
		ra_move(pswap);
	get_relevant_numbers(pswap);
	if (pswap->stack_b.numbers == 2)
		pswap->pivot.pivot_b = pswap->pivot.range[pswap->pivot.range_size - 1];
	if (pswap->stack_b.first < pswap->pivot.pivot_b)
		rb_move(pswap);
}

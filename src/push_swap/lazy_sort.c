/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lazy_sort.c                                        :+:      :+:    :+:   */
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
	if (pswap->lazy.range_size > pswap->stack_a.numbers)
		pswap->lazy.range_size = pswap->stack_a.numbers;
	if (pswap->lazy.range)
		pswap->lazy.range = ft_del(pswap->lazy.range);
	pswap->lazy.range = malloc(pswap->lazy.range_size * sizeof(int));


	//menor de los mayores
	pswap->lazy.range[i++] = pswap->stack_a.smallest;
	while (i < pswap->lazy.range_size)
	{
		pswap->lazy.range[i] = get_next_num(pswap->stack_a.stack, pswap->lazy.range[i - 1]);
		i++;
	}
}

size_t	miguel_sort(t_pswap *pswap)
{
	t_list	*stack_a;
	t_list	*stack_b;
	t_sequence	sequence_b;

	//define range
	pswap->move_counter = 0;
	//debug code

	get_range(pswap);

	// //debug code
	// printf("BOROBÓ\n");
	// for (size_t x = 0; x < pswap->lazy.range_size; x++)
	// 	printf("%d\n", pswap->lazy.range[x]);
	// if (has_num(pswap->lazy.range, pswap->lazy.range_size, 20))
	// 	printf("IT'S ALIVE!!!!\n");
	// exit_failure("FAILED!!!!", pswap);
	// //debug code

	while (pswap->stack_a.stack)
	{
		stack_a = pswap->stack_a.stack;
		while (stack_a)
		{
			get_range(pswap);
			if (has_num(pswap->lazy.range, pswap->lazy.range_size, *(int *)stack_a->content))
			{
				pb_move(pswap);
				// //debug code
				// printf("THE RANGE\n");
				// for(size_t p = 0; p < pswap->lazy.range_size; p++)
				// 	printf("%d\n", pswap->lazy.range[p]);
				// //debug code
			}
			stack_a = stack_a->next;
		}
	}
	// while (pswap->stack_b.stack)
	// {
	// 	ft_bzero(&sequence_b, sizeof(t_sequence));
	// 	get_relevant_numbers(pswap);
	// 	stack_b = pswap->stack_b.stack;
	// 	int i = 0;
	// 	while (*(int *)stack_b->content != pswap->stack_b.largest)
	// 	{
	// 		stack_b = stack_b->next;
	// 		i++;
	// 	}
	// 	sequence_b.r_moves = i;
	// 	sequence_b.rr_moves = pswap->stack_b.numbers - sequence_b.r_moves;
	// 	if (sequence_b.r_moves < sequence_b.rr_moves)
	// 		while (sequence_b.r_moves--)
	// 			rb_move(pswap);
	// 	else
	// 		while (sequence_b.rr_moves--)
	// 			rrb_move(pswap);
	// 	pa_move(pswap);
	// }


	ft_bzero(&sequence_b, sizeof(t_sequence));
	get_relevant_numbers(pswap);
	stack_b = pswap->stack_b.stack;
	int i = 0;
	while (*(int *)stack_b->content != pswap->stack_b.largest)
	{
		stack_b = stack_b->next;
		i++;
	}
	sequence_b.r_moves = i;
	sequence_b.rr_moves = pswap->stack_b.numbers - sequence_b.r_moves;
	if (sequence_b.r_moves < sequence_b.rr_moves)
		while (sequence_b.r_moves--)
			rb_move(pswap);
	else
		while (sequence_b.rr_moves--)
			rrb_move(pswap);
	pa_move(pswap);
	while (pswap->stack_b.stack)
	 	merge_sequence(pswap);
	return (pswap->move_counter);
}

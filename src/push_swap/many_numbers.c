/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   many_numbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 21:41:38 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/08 22:27:58 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Quick recursive to free the ordered list without touching the content. I need
** this to keep resetting the stack using the clone stack, since I run this
** function multiple times with different range sizes until I get the best
** result, so the stack needs to be reset to the way it was in the beginning.
*/

t_list	*lst_reset(t_list *list)
{
	if (list->next)
		list = lst_reset(list->next);
	else
		list = ft_del(list);
	return (list);
}

/*
** This function takes the stack in stack_a and sorts it using the algorithm in
** sequence_stacks, which pushes numbers to stack_b in ranges defined by
** test_range_size. We try all test_range_sizes from the initial one to 100.
**
** The working range size is defined as pivot.range size at the beginning and
** the move counter is reset.
**
** The best_move_sequence is initialized to SIZE_MAX. If the number of moves to
** sort the stack is less than the best_move_sequence, it replaces
** best_move_sequence and the associated test_range_size is saved as
** best_range_size.
**
** Then the stack is reset and the instruction set is deleted. The display bar
** is updated. Then we repeat until all test ranges up to 100 are tried.
**
** The first write hides the cursor to make the display bar prettier, and then
** shows it again once the testing is complete. This is not civilized... if you
** shut the program down during testing the cursor is still disappeared as I
** don't intercept signals. No points off for that in the eval though. ;p
**
** Lastly, since I don't save instruction sets because I like to make the CPU
** suffer, once we are finished testing we reset the move counter and stack_a
** one last time and set the range_size as the best_range_size - the one that
** generated the lowest number of moves - and we sequence the stacks again to
** get that move list. That is the list that will be printed on STDOUT.
*/

void	many_numbers(t_pswap *pswap)
{
	write(STDERR_FILENO, "\e[?25l\n\n", 8);
	while (++pswap->test_range_size <= 100)
	{
		pswap->pivot.range_size = pswap->test_range_size;
		pswap->move_counter = 0;
		sequence_stacks(pswap);
		if (pswap->move_counter < pswap->best_move_sequence)
		{
			pswap->best_move_sequence = pswap->move_counter;
			pswap->best_range_size = pswap->test_range_size;
		}
		pswap->stack_a.stack = lst_reset(pswap->stack_a.stack);
		pswap->stack_a.stack = clone_stack(pswap->stack_a_clone);
		if (pswap->instruction)
			ft_lstclear(&pswap->instruction, free);
		display_progress_bar(pswap);
	}
	write(STDERR_FILENO, "\e[?25h", 6);
	pswap->move_counter = 0;
	pswap->stack_a.stack = lst_reset(pswap->stack_a.stack);
	pswap->stack_a.stack = clone_stack(pswap->stack_a_clone);
	pswap->pivot.range_size = pswap->best_range_size;
	sequence_stacks(pswap);
}

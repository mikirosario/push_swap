/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 21:55:20 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/15 20:05:32 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** No mystery here. This function counts all the numbers for later reference.
*/

void	count_numbers(t_pswap *pswap)
{
	t_list	*stack_a;

	stack_a = pswap->stack_a.stack;
	while (stack_a)
	{
		stack_a = stack_a->next;
		pswap->numbers++;
	}
	pswap->stack_a.numbers = pswap->numbers;
}

/*
** This function will print all instructions to STDOUT once they are all
** generated. We use ft_putendl_fd so they all come out with newlines.
*/

void	print_instructions(t_pswap *pswap)
{
	t_list	*instructions;

	instructions = pswap->instruction;
	while (instructions)
	{
		ft_putendl_fd((char *)instructions->content, STDOUT_FILENO);
		instructions = instructions->next;
	}
}

/*
** Just an initialization function. The starting test_range size is the one
** after the one we set here, so if we start at 0 the first one will be 1, and
** for 9 the first one will be 10. For any series of numbers below 51 we start
** at 1. At or above 51 we start at 10. The works okay for up to 500 numbers.
**
** The length of the progress bar is set here at 100 - the initial
** test_range_size. It can be and is further tweaked in thhe progress bar
** function. The visual representations of the progress bar are saved in
** pbar.bar and pbar.empty with the characters for full and empty progress bars
** respectively. We use memset for that.
**
** Memory is reserved here for the position masks of stack a and stack b and we
** initialize the mask indices as needed (check the mask functions for details,
** it's a headache...).
**
** Lastsly, we get the largest and smallest numbers in the series using the
** binary tree search.
*/

void	init(t_pswap *pswap)
{
	t_bstnode	*bintree;

	if (pswap->numbers < 51)
		pswap->test_range_size = 0;
	else
		pswap->test_range_size = 9;
	pswap->pbar.len = 100 - pswap->test_range_size;
	ft_memset(pswap->pbar.bar, '#', 100);
	ft_memset(pswap->pbar.empty, '-', 100);
	pswap->stack_a.mask.vector = ft_calloc(pswap->numbers, sizeof(int));
	pswap->stack_b.mask.vector = ft_calloc(pswap->numbers, sizeof(int));
	pswap->stack_a.mask.start_index = 0;
	pswap->stack_a.mask.end_index = pswap->numbers;
	pswap->stack_b.mask.start_index = pswap->numbers;
	pswap->stack_b.mask.end_index = pswap->numbers;
	bintree = pswap->bintree;
	while (bintree->left)
		bintree = bintree->left;
	pswap->smallest = (int)bintree->data;
	bintree = pswap->bintree;
	while (bintree->right)
		bintree = bintree->right;
	pswap->largest = (int)bintree->data;
}

/*
** This function clones the STATUS of the stack passed as original_stack. It
** does NOT clone the contents, only the RELATIONSHIP between the contents.
**
** By making a clone at the beginning of the program, I can then clone the clone
** at any point in the program to get the original stack a back. Bit of a quick
** fix since I wasn't anticipating having to reuse stack a at first. :p
*/

t_list	*clone_stack(t_list *original_stack)
{
	t_list	*clone_stack;

	clone_stack = NULL;
	while (original_stack)
	{
		if (clone_stack == NULL)
			clone_stack = ft_lstnew(original_stack->content);
		else
			ft_lstadd_back(&clone_stack, ft_lstnew(original_stack->content));
		original_stack = original_stack->next;
	}
	return (clone_stack);
}

/*
** First we declare the pswap struct and zero it.
**
** Then we generate stack_a and stack_b (which is just initialized to NULL) as
** linked lists.
**
** Then we count the numbers.
**
** If there is only one number, all that was for nothing. We exit. :p
**
** Otherwise, we then initialize some variables.
**
** Then we generate instructions, which will return 1 for as long as the list
** remains unordered, and return 0 when the list is ordered.
**
** When we're done, we print the instructions, if any.
**
** Then we exit.
*/

int	main(int argc, char **argv)
{
	t_pswap	pswap;

	(void)argc;
	ft_bzero(&pswap, sizeof(t_pswap));
	generate_stacks(argv, &pswap);
	pswap.stack_a_clone = clone_stack(pswap.stack_a.stack);
	pswap.best_move_sequence = SIZE_MAX;
	count_numbers(&pswap);
	array_my_tree(&pswap);
	if (pswap.numbers > 1)
	{
		init(&pswap);
		while (generate_instructions(&pswap))
		{
		}
		print_instructions(&pswap);
	}
	exit_success(&pswap);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 21:55:20 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/25 23:29:27 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** No mystery here. This function counts all the numbers for later reference.
*/

void	count_numbers(t_pswap *pswap)
{
	t_list	*stack_a;

	stack_a = pswap->stack_a;
	while (stack_a)
	{
		stack_a = stack_a->next;
		pswap->numbers++;
	}
	pswap->stack_a_numbers = pswap->numbers;
}

/*
** This function will print all instructions to STDOUT once they are all
** generated. We use ft_putendl_fd so they all come out with newlines.
*/

void	print_instructions(t_pswap *pswap)
{
	t_list	*instructions;

	//debug code
	printf("ITERATION: %zu\n", pswap->tonti);
	//debug code

	instructions = pswap->lst;
	while (instructions)
	{
		ft_putendl_fd((char *)instructions->content, STDOUT_FILENO);
		instructions = instructions->next;
	}

	//debug code
	printf("Number of Movements: %zu\n", pswap->move_counter);
	printf("STACK A\n");
	for (t_list *lst = pswap->stack_a; lst; lst = lst->next)
		printf("%d\n", *(int *)lst->content);
	printf("STACK B\n");
	for (t_list *lst = pswap->stack_b; lst; lst = lst->next)
		printf("%d\n", *(int *)lst->content);
	//debug code
}

/*
** Just an initialization function. Essentially we get the largest and smallest
** numbers in the series using the binary tree and prepare the vectors for the
** position maps.
*/
void	init(t_pswap *pswap)
{
	t_bstnode	*bintree;

	pswap->mask_a.vector = ft_calloc(pswap->numbers, sizeof(int));
	pswap->mask_b.vector = ft_calloc(pswap->numbers, sizeof(int));
	pswap->mask_a.start_index = 0;
	pswap->mask_a.end_index = pswap->numbers;
	pswap->mask_b.start_index = pswap->numbers;
	pswap->mask_b.end_index = pswap->numbers;
	bintree = pswap->bintree;
	while (bintree->left)
		bintree = bintree->left;
	pswap->smallest = (int)bintree->data;
	bintree = pswap->bintree;
	while(bintree->right)
		bintree = bintree->right;
	pswap->largest = (int)bintree->data;
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
	count_numbers(&pswap);
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

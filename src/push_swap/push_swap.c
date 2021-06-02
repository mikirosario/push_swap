/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 21:55:20 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/02 18:23:10 by mrosario         ###   ########.fr       */
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

	// //debug code
	// printf("ITERATION: %zu\n", pswap->tonti);
	// //debug code

	instructions = pswap->instruction;
	while (instructions)
	{
		ft_putendl_fd((char *)instructions->content, STDOUT_FILENO);
		instructions = instructions->next;
	}
	// //debug
	// printf("Number of Movements: %zu\n", pswap->move_counter);
	// //debug

	// //debug code
	// printf("STACK A\n");
	// for (t_list *lst = pswap->stack_a.stack; lst; lst = lst->next)
	// 	printf("%d\n", *(int *)lst->content);
	// printf("STACK B\n");
	// for (t_list *lst = pswap->stack_b.stack; lst; lst = lst->next)
	// 	printf("%d\n", *(int *)lst->content);
	// printf("Number of Movements: %zu\n", pswap->move_counter);
	// //debug code
}

/*
** Just an initialization function. Essentially we get the largest and smallest
** numbers in the series using the binary tree and prepare the vectors for the
** position maps.
*/
void	init(t_pswap *pswap)
{
	t_bstnode	*bintree;

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
	while(bintree->right)
		bintree = bintree->right;
	pswap->largest = (int)bintree->data;
}

static void	in_order_traversal(t_pswap *pswap, t_bstnode *root)
{
	if (root != NULL)
	{
		in_order_traversal(pswap, root->left);
		//printf("NUM: %d POS: %d\n", (int)root->data, pswap->desired_pos++);
		pswap->array_tree[pswap->desired_pos++] = root;
		in_order_traversal(pswap, root->right);
	}
}

/*
** Sometimes you just REALLY want to make that binary tree you were using into
** an array. Amirite? For those times, in this program, there is this function.
** Best of both worlds, I always say. Or maybe I've just had enough of misuing
** binary trees in expensive calculations for the sake of practice. xD
**
** So I'm going to create an array of bst_node pointers. Let's  get cracking!
*/

void	array_my_tree(t_pswap *pswap)
{
	pswap->array_tree = ft_calloc(pswap->numbers, sizeof(t_bstnode *));
	pswap->desired_pos = 0;
	in_order_traversal(pswap, pswap->bintree);

	// //DEBUG COD
	// printf("\n<<<<<<<ARRAY TREE>>>>>>>\n");
	// for (size_t i = 0; i < pswap->numbers; i++)
	// {
	// 	printf("%d\n", (int)(pswap->array_tree[i])->data);
	// }
	// //debug c
}

// void	clone_stack(t_pswap *pswap)
// {
// 	t_list
// }

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
	//clone_stack(&pswap);
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

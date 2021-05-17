/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_instructions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 18:53:38 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/17 20:30:40 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Get position in stack_b of integer passed as num. If the integer is not in
** stack a, -1 is returned. Numbers in stack_b are returned to stack_a in FILO.
** Therefore, a number in position 0 of stack_b, when there are three numbers in
** stack_b, will actually be in position 2 of stack_a once returned. So we take
** stack_b_numbers - (i + 1) to get the stack_a relative position.
*/

int	get_stack_b_pos(t_pswap *pswap, int num)
{
	t_list	*stack;
	int		i;

	i = 0;
	stack = pswap->stack_b;
	while (stack)
	{
		if (*(int *)stack->content == num)
		//0 == numbers - 1
			return (pswap->stack_b_numbers - (i + 1));
		i++;
		stack = stack->next;
	}
	return (-1);
}

/*
** Get position in stack_a of integer passed as num. If the integer is not in
** stack a, -1 is returned. If there are numbers in stack_b, they will displace
** the numbers in stack_a downwards when reincorporated, so the effective
** position of a stack a number is always its position + stack_b_numbers.
*/

int	get_stack_a_pos(t_pswap *pswap, int num)
{
	t_list	*stack;
	int		i;

	i = 0;
	stack = pswap->stack_a;
	while (stack)
	{
		if (*(int *)stack->content == num)
			return (i + pswap->stack_b_numbers);
		i++;
		stack = stack->next;
	}
	return (-1);
}

/*
** The function record_offset subtracts the actual position of the number passed
** as num in stack a from its desired position pased as desired_pos to get the
** current offset from the desired position and place it in the mask at the
** number's actual current position in stack_a.
*/

void	record_offset(t_pswap *pswap, int desired_pos, int num)
{
	int	actual_pos;

	//IF IS IN STACK A; STACK A POS IN MASK A
	actual_pos = get_stack_a_pos(pswap, num);
	//IF IS IN STACK B; STACK B POS IN MASK B
	if (actual_pos < 0)
		actual_pos = get_stack_b_pos(pswap, num);
	pswap->mask_a.vector[actual_pos] = desired_pos - actual_pos;
}

/*
** Generates a mask that indicates the offset between a number in stack_a and
** its sorted position in the stack.
**
** The variable i indicates where the number *should* be by using the binary
** tree to find all the numbers via in-order traversal, and then calls
** record_offset to record the offset.
*/

void	in_order_traversal(t_pswap *pswap, t_bstnode *root)
{
	if (root != NULL)
	{
		in_order_traversal(pswap, root->left);
		//printf("NUM: %d POS: %d\n", (int)root->data, pswap->desired_pos++);
		record_offset(pswap, pswap->desired_pos++, (int)root->data);
		in_order_traversal(pswap, root->right);
	}
}

void	generate_position_map(t_pswap *pswap)
{
	size_t	i;
	int		*ptr;

	if (!pswap->mask_a.vector)
		pswap->mask_a.vector = ft_calloc(pswap->numbers, sizeof(int));
	if (!pswap->mask_b.vector)
		pswap->mask_b.vector = ft_calloc(pswap->numbers, sizeof(int));
	//Numbers pushed onto stack_b will not count for mask a. So if we have 1 number on stack_b
	//then mask_a will begin at position 1 rather than zero. Likewise, numbers in stack_a will
	//will not count for mask b, so if we have 5 numbers in stack_a, then mask_b will begin at
	//position five. Use the indices to get only the relevant parts of the position mask vectors.
	pswap->mask_a.start_index = pswap->stack_b_numbers;
	pswap->mask_b.start_index = pswap->stack_a_numbers;
	pswap->desired_pos = 0;
	in_order_traversal(pswap, pswap->bintree);
	i = pswap->numbers - 1;
	ptr = pswap->mask_b.vector;
	while (i)
	{
		*ptr++ = pswap->mask_a.vector[i--];
	}
	printf("STACK A POS MAP:\n");
	for(size_t x = pswap->stack_b_numbers; x < pswap->numbers; x++)
	{
		printf("%d\n", pswap->mask_a.vector[x]);
	}
	printf("STACK B POS MAP:\n");
	for(size_t x = pswap->stack_a_numbers; x < pswap->numbers; x++)
	{
		printf("%d\n", pswap->mask_b.vector[x]);
	}
}

// void	three_case(t_pswap *pswap)
// {
// 	t_list	*stack_a;
// }

char	is_sorted(t_pswap *pswap)
{
	t_list	*stack_a;

	if (pswap->stack_b)
		return (0);
	stack_a = pswap->stack_a;
	while (stack_a->next)
	{
		if (*(int *)stack_a->content > *(int *)stack_a->next->content)
			return (0);
		stack_a = stack_a->next;
	}
	return (1);
}

void	generate_instructions(t_pswap *pswap)
{
	t_list	*stack_a;

	stack_a = pswap->stack_a;
	// if (is_sorted(pswap))
	// 	return ;
	while (stack_a)
	{
		stack_a = stack_a->next;
		pswap->numbers++;
	}
	pswap->stack_a_numbers = pswap->numbers;
	// printf("NUMBER COUNT: %zu\n", pswap->numbers);
	pb_move(pswap);
	pb_move(pswap);
	ra_move(pswap);
	pb_move(pswap);
	sb_move(pswap);
	ra_move(pswap);
	generate_position_map(pswap);

	// if (pswap->numbers == 2)
	// 	ft_putendl_fd("sa", STDOUT_FILENO);
	// else if (pswap->numbers == 3)
		
}

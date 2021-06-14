/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_position_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 03:58:49 by miki              #+#    #+#             */
/*   Updated: 2021/06/14 16:42:06 by mrosario         ###   ########.fr       */
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
	stack = pswap->stack_b.stack;
	while (stack)
	{
		if (*(int *)stack->content == num)
			return (pswap->stack_b.numbers - (i + 1));
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
	stack = pswap->stack_a.stack;
	while (stack)
	{
		if (*(int *)stack->content == num)
			return (i + pswap->stack_b.numbers);
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

	actual_pos = get_stack_a_pos(pswap, num);
	if (actual_pos < 0)
		actual_pos = get_stack_b_pos(pswap, num);
	pswap->stack_a.mask.vector[actual_pos] = desired_pos - actual_pos;
}

/*
** Generates a mask that indicates the offset between a number in stack_a and
** its sorted position in the stack.
**
** The variable i indicates where the number *should* be by using the binary
** tree to find all the numbers via in-order traversal, and then calls
** record_offset to record the offset.
*/

static void	in_order_traversal(t_pswap *pswap, t_bstnode *root)
{
	if (root != NULL)
	{
		in_order_traversal(pswap, root->left);
		record_offset(pswap, pswap->desired_pos++, (int)root->data);
		in_order_traversal(pswap, root->right);
	}
}

/*
** This function generates two arrays that record the offset between the current
** position of a number in the series and its desired position. Offsets are
** stack-invariant. The first number in stack_a is considered to neighbour the
** first number in stack_b, such that stack_b numbers effectively displace
** stack_a numbers downward for the purpose of determining their position.
** Consequently, pushing numbers between stacks will NOT affect their relative
** positions. ONLY swaps and rotations will change the position map.
**
** Offset positions may be positive or negative. A positive offset means that
** the number must move down the given number of positions in stack_a and up the
** given number of positions in stack_b, and a negative offset vice versa.
**
** The t_mask object includes two indices, start_index and end_index, which
** record where the mask begins and ends for each stack. These ARE affected by
** pushing and can be used to get offsets at any time. At any given time,
** mask_x.vector[start_index] corresponds to the offset position of the first
** number in the stack_x. Note that while stacks are linked lists, the masks are
** simple vectors and t_mask is just a sole object, NOT the start of a linked
** list.
**
** For the following series these would be the position offset vectors:
**
** STACK A	STACK B		OFFSET
**	 4					  4		Must move down 4 times for desired position.
**	 1					  0		Already in desired position.
**	 0					 -2		Must move up 2 times for desired position.
**	 3					  0		Already in desired position.
**	 2					 -2		Must move up 2 times for desired position.
**
** They do not change when pushed between stacks. Thus, after pushing the top
** two numbers of stack_a to stack_b:
**
** STACK A	STACK B		OFFSET
**	 0					  -2
**	 3					   0
**	 2					  -2
**			  1			   0
**			  4			   4
**
** If we swap the numbers in stack_b (sb), however, the offset vectors change...
**
** STACK A	STACK B		OFFSET
**	 0					  -2
**	 3					   0
**	 2					  -2
**			  4			   3
**			  1			   1
**
** You can see that moving a number up stack_b decrements its offset, and moving
** it down increments it. The inverse is true for stack_a, so if we swap the
** first two numbers in stack_a (sa):
**
** STACK A	STACK B		OFFSET
**	 3					   1
**	 0					  -3
**	 2					  -2
**			  4			   3
**			  1			   1
**
** Also note that the sum of all offsets is ALWAYS zero. This can be used as a
** checksum. If the sum of all offsets is ever anything but zero, the position
** mask CANNOT be true. An offset also MUST be untrue if any offset or any sum
** of the offsets is ever greater than the total numbers in the series or less
** than negative total numbers in the series. This is also a checksum.
**
** If the series of numbers is in perfect ascending order, all offsets will be
** zero, even if they are split between stacks. When all offsets become zero,
** any remaining numbers in stack_b can simply be pushed to stack_a to sort the
** numbers.
*/

void	generate_position_map(t_pswap *pswap)
{
	size_t	i;
	int		*ptr;

	pswap->desired_pos = 0;
	in_order_traversal(pswap, pswap->bintree);
	i = pswap->numbers;
	ptr = pswap->stack_b.mask.vector;
	while (i--)
	{
		*ptr++ = pswap->stack_a.mask.vector[i];
	}
}

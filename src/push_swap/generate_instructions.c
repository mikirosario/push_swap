/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_instructions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 18:53:38 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/21 22:22:47 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** This function adds a move to the instruction list that will be output by the
** program. If consecutive sa/sb, ra/rb or rra/rrb moves are requested, they
** will be condensed into a single ss, rr and rrr, respectively.
*/

void	add_move_to_list(t_pswap *pswap, char *move)
{
	t_list	*tmp;
	t_list	*last;

	last = ft_lstlast(pswap->lst);
	if (last && ((!ft_strcmp(move, "sa") && !ft_strcmp(last->content, "sb"))
	|| (!ft_strcmp(move, "sb") && !ft_strcmp(last->content, "sa"))))
		*(char *)((last->content + 1)) = 's';
	else if (last && ((!ft_strcmp(move, "ra") && !ft_strcmp(last->content, "rb"))
	|| (!ft_strcmp(move, "rb") && !ft_strcmp(last->content, "ra"))))
		*(char *)((last->content + 1)) = 'r';
	else if (last && ((!ft_strcmp(move, "rra") && !ft_strcmp(last->content, "rrb"))
	|| (!ft_strcmp(move, "rrb") && !ft_strcmp(last->content, "rra"))))
		*(char *)((last->content + 2)) = 'r';
	else
	{
		tmp = ft_lstnew(ft_strdup(move));
		if (!pswap->lst)
			pswap->lst = tmp;
		else
			ft_lstadd_back(&pswap->lst, tmp);
	}
}

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

	//Numbers pushed onto stack_b will not count for mask a. So if we have 1 number on stack_b
	//then mask_a will begin at position 1 rather than zero. Likewise, numbers in stack_a will
	//will not count for mask b, so if we have 5 numbers in stack_a, then mask_b will begin at
	//position five. Use the indices to get only the relevant parts of the position mask vectors.
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

int	is_sorted(t_list *stack)
{
	if (stack == NULL || stack->next == NULL)
		return (1);
	while (stack->next)
	{
		if (*(int *)stack->content > *(int *)stack->next->content)
			return (0);
		stack = stack->next;
	}
	return (1);
}

/*
** Determines whether the first two values of stack_a should definitely be
** swapped.
**
** The first two values of stack_a should definitely be swapped if the first
** value is greater than the second value (they are unordered) and they are
** contiguous in the series (in a series "0 2 5", 2 and 5 are contiguous, 0 and
** 5 are not).
**
** If the above conditions are met, 1 is returned. Otherwise, 0 is returned. If
** there are less than two numbers in the stack, 0 is returned.
*/

int should_swap_stack_a(t_pswap *pswap)
{
	int	first;
	int	second;

	if (pswap->stack_a_numbers > 1)
	{
		first = *(int *)pswap->stack_a->content;
		second = *(int *)pswap->stack_a->next->content;
		if (first > second && are_contiguous(pswap, second, first))
			return (1);
	}
	return (0);
}

/*
** Determines whether the first two values of stack_b should definitely be
** swapped.
**
** The first two values of stack_b should definitely be swapped if the first
** value is less than the second value (they are unordered) and they are
** contiguous in the series (in a series "0 2 5", 2 and 5 are contiguous, 0 and
** 5 are not).
**
** If the above conditions are met, 1 is returned. Otherwise, 0 is returned. If
** there are less than two numbers in the stack, 0 is returned.
*/

int should_swap_stack_b(t_pswap *pswap)
{
	int	first;
	int	second;

	if (pswap->stack_b_numbers > 1)
	{
		first = *(int *)pswap->stack_b->content;
		second = *(int *)pswap->stack_b->next->content;
		if (first < second && are_contiguous(pswap, first, second))
			return (1);
	}
	return (0);
}

// void	rotate_stack_a(t_pswap *pswap)
// {
// 	long int		top_value;
// 	long int		bottom_value;
// 	size_t	i;

// 	generate_position_map(pswap);
// 	i = pswap->mask_a.start_index;
// 	top_value = pswap->mask_a.vector[i];
// 	bottom_value = pswap->mask_a.vector[pswap->numbers - 1];

// 	if (top_value < 0)
// 		top_value *= -1;
// 	if (bottom_value < 0)
// 		bottom_value *= -1;
// 		//bottom needs to move more than top
// 	if (top_value < bottom_value)
// 		rra_move(pswap);
// 		//top needs to move more than bottom, or same as bottom
// 	else
// 		ra_move(pswap);
// }

void	rotate_stack(t_pswap *pswap, t_list *stack)
{
	long int		top_value;
	long int		bottom_value;
	t_mask			*mask;
	size_t	i;

	generate_position_map(pswap);
	if (stack == NULL)
		return ;
	if (stack == pswap->stack_a)
		mask = &pswap->mask_a;
	else
		mask = &pswap->mask_b;
	i = mask->start_index;
	top_value = mask->vector[i];
	bottom_value = mask->vector[pswap->numbers - 1];
	if (top_value < 0)
		top_value *= -1;
	if (bottom_value < 0)
		bottom_value *= -1;
		//bottom needs to move more than top
	if (top_value < bottom_value)
		rra_move(pswap);
		//top needs to move more than bottom, or same as bottom
	else
		ra_move(pswap);
}

int	should_rotate_stack_a(t_pswap *pswap)
{
	int	first;
	int last;
	
	if (pswap->stack_a_numbers > 2)
	{
		first = *(int *)pswap->stack_a->content;
		last = *(int *)(ft_lstlast(pswap->stack_a))->content;
		if (first > last && are_contiguous(pswap, last, first))
			return (1);
	}
	return (0);
}

int	should_rotate_stack_b(t_pswap *pswap)
{
	int	first;
	int last;
	
	if (pswap->stack_b_numbers > 2)
	{
		first = *(int *)pswap->stack_b->content;
		last = *(int *)(ft_lstlast(pswap->stack_b))->content;
		if (first < last && are_contiguous(pswap, first, last))
			return (1);
	}
	return (0);
}

/*
** First stack_a and stack_b are checked to see if their first two values should
** definitely be swapped to order them. If a swap is needed in both stacks it is
** automatically replaced by 'ss_move' in the instructions output to the user.
**
** Then a position map is generated for both stacks indicating offset between
** the position of a number in the stack and its desired position.
**
** Then the function uses the position map to ask if the numbers are already
** ordered. Numbers may be ordered even if they are split between stacks, as
** long as they will be properly ordered after all numbers return from stack b.
** The function is_ordered automatically returns all numbers from stack_b to
** stack_a if the numbers in the series are ordered.
**
** Otherwise, if there are three numbers, the three number solver is used.
*/

int	generate_instructions(t_pswap *pswap)
{
	// printf("NUMBER COUNT: %zu\n", pswap->numbers);
	// pb_move(pswap);
	// pb_move(pswap);
	// ra_move(pswap);
	// pb_move(pswap);
	// sb_move(pswap);
	// ra_move(pswap);
	//always swap *contiguous* numbers in first two positions of stack_a if the

	// // first is greater than the second, and of stack_b if the first is less
	// // than the second.
	// if (should_swap_stack_a(pswap))
	// 	sa_move(pswap);
	// if (should_swap_stack_b(pswap))
	// 	sb_move(pswap);
	// //always rotate if first and last numbers are contiguous and first is greater
	// //than last in stack_a or less than last in stack_b.
	// if (should_rotate_stack_a(pswap))
	// 	rotate_stack(pswap, pswap->stack_a);
	// if (should_rotate_stack_b(pswap))
	// 	rotate_stack(pswap, pswap->stack_b);

	// if (pswap->stack_a_numbers > 1 &&
	// *(int *)pswap->stack_a->content > *(int *)pswap->stack_a->next->content
	//  && are_contiguous(pswap, *(int *)pswap->stack_a->content,
	// *(int *)pswap->stack_a->next->content))
	// 	sa_move(pswap);
	// if (pswap->stack_b_numbers > 1 &&
	// *(int *)pswap->stack_b->content < *(int *)pswap->stack_b->next->content
	//  && are_contiguous(pswap, *(int *)pswap->stack_b->content,
	// *(int *)pswap->stack_b->next->content))
	// 	sb_move(pswap);
	generate_position_map(pswap);
	if (is_ordered(pswap))
		return (0);
	if (pswap->numbers <= 3)
		three_numbers(pswap);
	else if (pswap->numbers <= 5)
		five_numbers(pswap);
	//debug code
	static int x = 1;
	printf("UNSORTED STACK A %d\n", x);
	for (t_list *lst = pswap->stack_a; lst; lst = lst->next)
		printf("%d\n", *(int *)lst->content);
	printf("MASK A %d\n", x++);
	for (size_t i = pswap->mask_a.start_index; i < pswap->numbers; i++)
		printf("%d\n", pswap->mask_a.vector[i]);
	// if (equal_offsets(pswap))
	// {
	// 	tmp = ft_lstnew(ft_strdup("ra"));
	// 	if (!pswap->lst)
	// 		pswap->lst = tmp;
	// 	else
	// 		ft_lstadd_back(&pswap->lst, tmp);
	// }
	return (1);

	// if (pswap->numbers == 2)
	// 	ft_putendl_fd("sa", STDOUT_FILENO);
	// else if (pswap->numbers == 3)
		
}

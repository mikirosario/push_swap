/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_instructions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 18:53:38 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/08 22:12:02 by mrosario         ###   ########.fr       */
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

	last = ft_lstlast(pswap->instruction);
	if (last && ((!ft_strcmp(move, "sa") && !ft_strcmp(last->content, "sb")) \
	 || (!ft_strcmp(move, "sb") && !ft_strcmp(last->content, "sa"))))
		*(char *)((last->content + 1)) = 's';
	else if (last && ((!ft_strcmp(move, "ra") \
	 && !ft_strcmp(last->content, "rb")) \
	 || (!ft_strcmp(move, "rb") && !ft_strcmp(last->content, "ra"))))
		*(char *)((last->content + 1)) = 'r';
	else if (last && ((!ft_strcmp(move, "rra") \
	 && !ft_strcmp(last->content, "rrb")) \
	 || (!ft_strcmp(move, "rrb") && !ft_strcmp(last->content, "rra"))))
		*(char *)((last->content + 2)) = 'r';
	else
	{
		tmp = ft_lstnew(ft_strdup(move));
		if (!pswap->instruction)
			pswap->instruction = tmp;
		else
			ft_lstadd_back(&pswap->instruction, tmp);
		pswap->move_counter++;
	}
}

/*
** Once stack_a is sequenced, this function will rotate it into the proper order
** so that it is sorted with the smallest value at the top and the largest at
** the bottom, using the least number of moves. This is done using the position
** map to determine the distance between the first value in the list and its
** desired position as compared with the median of the number of numbers in the
** stack.
**
** If stack_a is properly sequenced but requires rotation then the first
** position map offset in mask_a will always be positive, because since stack_b
** is empty there is no preceding position to move into. Furthermore, it will
** always be greater than 0, because if it were 0, then the entire stack would
** already be ordered.
**
** If the first position map offset in mask_a is greater than the median of the
** number of numbers in the stack, then the shorter distance is to rotate the
** first value to the bottom using ra_move. Otherwise, the shorter distance is
** to reverse rotate the last value to the top using rra_move.  Equidistant
** numbers will prefer reverse rotation. A function pointer is used to get the
** right function.
*/

void	sort_rotate_stack_a(t_pswap *pswap)
{
	void		(*rotate)(t_pswap *);
	long int	median;
	size_t		i;

	median = pswap->numbers / 2;
	generate_position_map(pswap);
	if (pswap->stack_a.mask.vector[0] > median)
	{
		rotate = ra_move;
		i = pswap->numbers - pswap->stack_a.mask.vector[0];
	}
	else
	{
		rotate = rra_move;
		i = pswap->stack_a.mask.vector[0];
	}
	while (i--)
		rotate(pswap);
}

/*
** First the is_ordered function checks to see if the numbers are already
** ordered. If they are it will return true, and this function will return 0 to
** indicate to the calling function that instruction generation has ended. The
** is_ordered check is stack-invariant. If the numbers are ordered but spread
** between stack_a and stack_b, the function will use pa_move to return all
** stack_b numbers to stack_a and return true.
**
** If the numbers are not ordered then we will check whether stack_b exists and
** if it does not exist whether stack_a's numbers are sequenced. Sequenced means
** that, while not in their proper position, they are in the right sequence, for
** example: 2 0 1 is in the right sequence, you just need to rotate it so 0 is
** in the first position.
**
** If there are numbers in stack_b or stack_a is not yet sequenced, we defer to
** the solvers.
**
** The solver three_numbers will solve for two and three numbers. The solver
** six_numbers will solve for four to six numbers. The solver many_numbers will
** solve for any amount of numbers above six.
*/

int	generate_instructions(t_pswap *pswap)
{
	if (pswap->stack_b.stack == NULL && \
	stack_a_is_sequenced(pswap, &pswap->stack_a))
		sort_rotate_stack_a(pswap);
	if (is_ordered(pswap))
		return (0);
	else if (pswap->numbers <= 3)
		three_numbers(pswap);
	else if (pswap->numbers <= 6)
		six_numbers(pswap);
	else
		many_numbers(pswap);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 11:57:03 by miki              #+#    #+#             */
/*   Updated: 2021/05/21 17:30:43 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Determines whether the first pair of values in the stack passed as an
** argument are ordered.
**
** If they are in ascending order, 1 is returned. Otherwise, 0 is returned.
** If a NULL pointer is passed or there aren't two values in the stack, 1 is
** returned.
*/

// int	first_pair_ordered(t_list *stack)
// {
// 	if ((stack == NULL || stack->next == NULL)
// 	 || *(int *)stack->content < *(int *)stack->next->content)
// 			return (1);
// 	return (0);
// }

/*
** Determines whether two numbers are contiguous in the series. The binary tree
** is used for traversal to save time. Equal values are not allowed by the
** program so that should never happen, but just in case I have the function
** throw a conspicuous error if it ever did.
**
** Although int arguments are labelled smaller and larger, the function will
** actually tolerate it if the larger number is passed as 'smaller' and the
** 'smaller' as larger - they will just be swapped.
**
** If values are found in the series that are between the two numbers passed as
** arguments, the function returns 0. Otherwise, the values are deemed
** contiguous and the function returns 1.
*/

int	are_contiguous(t_pswap *pswap, int smaller, int larger)
{
	int			tmp;
	t_bstnode	*ret;

	if (smaller == larger)
		exit_failure("are_contiguous function received equal values", pswap);
	if (smaller - larger == 1 || smaller - larger == -1)
		return (1);
	if (smaller > larger)
	{
		tmp = smaller;
		smaller = larger;
		larger = tmp;
	}
	ret = NULL;
	tmp = smaller + 1;
	while (ret == NULL && tmp < larger)
		ret = ft_bintree_search(pswap->bintree, (long long int)tmp++);
	if (ret == NULL)
		return (1);
	return (0);
}

int	push_down(t_pswap *pswap)
{
	t_list	*tmp;

	if (pswap->stack_a_numbers > 1)
	{
		tmp = ft_lstlast(pswap->stack_a);
		if (*(int *)pswap->stack_a->content - *(int *)tmp->content == 1)
		{
			ra_move(pswap);
			return (1);
		}
	}
	return (0);
}

// int	equal_offsets(t_pswap *pswap)
// {
// 	size_t	index_a;
// 	size_t	index_b;
// 	int		first_offset;
// 	int		offset;

// 	index_a = pswap->mask_a.start_index;
// 	index_b = pswap->mask_b.start_index;
// 	if (pswap->stack_b_numbers)
// 		first_offset = pswap->mask_b.vector[index_b++];
// 	else
// 		first_offset = pswap->mask_a.vector[index_a++];
// 	if (index_b < pswap->numbers)
// 		offset = pswap->mask_b.vector[index_b];
// 	else if (index_a < pswap->numbers)
// 		offset = pswap->mask_a.vector[index_a];
// 	if (offset > 0 || offset == first_offset)
// 		return (0);
// 	while (index_b < pswap->numbers - 1)
// 			if (offset != pswap->mask_b.vector[index_b++])
// 				return (0);
// 	while (index_a < pswap->numbers - 1)
// 		if (offset != pswap->mask_a.vector[index_a++])
// 			return (0);
// 	ra_move(pswap);
// 	return (1);
// }
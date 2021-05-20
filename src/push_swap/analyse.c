/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 11:57:03 by miki              #+#    #+#             */
/*   Updated: 2021/05/20 15:49:59 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
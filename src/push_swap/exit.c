/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 05:41:21 by miki              #+#    #+#             */
/*   Updated: 2021/06/02 10:23:43 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	freeme(t_pswap *pswap)
{
	if (pswap->stack_a.stack)
		ft_lstclear(&pswap->stack_a.stack, free);
	if (pswap->stack_b.stack)
		ft_lstclear(&pswap->stack_b.stack, free);
	if (pswap->stack_a.mask.vector)
		pswap->stack_a.mask.vector = ft_del(pswap->stack_a.mask.vector);
	if (!pswap->stack_b.mask.vector)
		pswap->stack_b.mask.vector = ft_del(pswap->stack_b.mask.vector);
	pswap->bintree = ft_bintree_free(pswap->bintree);
	if (pswap->bintree)
		pswap->bintree = ft_bintree_free(pswap->bintree);
	if (pswap->array_tree)
		pswap->array_tree = ft_del(pswap->array_tree);
	if (pswap->pivot.range)
		pswap->pivot.range = ft_del(pswap->pivot.range);
	if (pswap->instruction)
		ft_lstclear(&pswap->instruction, free);
}

void	print_error(char *error_msg, char *ansi_color_code)
{
	write(STDERR_FILENO, ansi_color_code, ft_strlen(ansi_color_code));
	ft_putendl_fd(error_msg, STDERR_FILENO);
	write(STDERR_FILENO, RESET, 4);
}

void	exit_failure(char *error_msg, t_pswap *pswap)
{
	if (error_msg)
		print_error(error_msg, RED);
	freeme(pswap);
	exit(EXIT_FAILURE);
}

void	exit_success(t_pswap *pswap)
{
	freeme(pswap);
	exit(EXIT_SUCCESS);
}

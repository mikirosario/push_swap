/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 05:41:21 by miki              #+#    #+#             */
/*   Updated: 2021/05/24 05:41:44 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	freeme(t_pswap *pswap)
{
	if (pswap->stack_a)
		ft_lstclear(&pswap->stack_a, free);
	if (pswap->stack_b)
		ft_lstclear(&pswap->stack_b, free);
	if (pswap->mask_a.vector)
		pswap->mask_a.vector = ft_del(pswap->mask_a.vector);
	if (!pswap->mask_b.vector)
		pswap->mask_b.vector = ft_del(pswap->mask_b.vector);
	pswap->bintree = ft_bintree_free(pswap->bintree);
	if (pswap->bintree)
		pswap->bintree = ft_bintree_free(pswap->bintree);
	if (pswap->lst)
		ft_lstclear(&pswap->lst, free);
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

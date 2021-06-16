/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 05:41:21 by miki              #+#    #+#             */
/*   Updated: 2021/06/16 19:16:13 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** Quick recursive to free the ordered list without touching the content. I need
** this to keep resetting the stack using the clone stack, since I run this
** function multiple times with different range sizes until I get the best
** result, so the stack needs to be reset to the way it was in the beginning.
*/

t_list	*lst_reset(t_list *list)
{
	if (list->next)
		lst_reset(list->next);
	list = ft_del(list);
	return (list);
}

/*
** This function frees everything that may or may not need to be freed. ;)
*/

void	freeme(t_pswap *pswap)
{
	if (pswap->stack_a.stack)
		ft_lstclear(&pswap->stack_a.stack, free);
	if (pswap->stack_b.stack)
		ft_lstclear(&pswap->stack_b.stack, free);
	if (pswap->stack_a_clone)
		pswap->stack_a_clone = lst_reset(pswap->stack_a_clone);
	if (pswap->stack_a.mask.vector)
		pswap->stack_a.mask.vector = ft_del(pswap->stack_a.mask.vector);
	if (pswap->stack_b.mask.vector)
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

/*
** This function prints the string pointed to by the pointer passed as error_msg
** using the colour passed as ANSI colour-code to STDERR and then resets the
** colour.
*/

void	print_error(char *error_msg, char *ansi_color_code)
{
	write(STDERR_FILENO, ansi_color_code, ft_strlen(ansi_color_code));
	ft_putendl_fd(error_msg, STDERR_FILENO);
	write(STDERR_FILENO, RESET, 4);
}

/*
** This function is called to exit the program due to an error. I'd do a signal
** catch too, but we aren't allowed to use signal for this project.
*/

void	exit_failure(char *error_msg, t_pswap *pswap)
{
	if (error_msg)
		print_error(error_msg, RED);
	freeme(pswap);
	exit(EXIT_FAILURE);
}

/*
** This function is called to exit the program normally.
*/

void	exit_success(t_pswap *pswap)
{
	freeme(pswap);
	exit(EXIT_SUCCESS);
}

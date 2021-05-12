/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 20:02:24 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/12 20:04:29 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	freeme(t_checker *checker)
{
	if (checker->stack_a)
		ft_lstclear(&checker->stack_a, free);
	if (checker->stack_b)
		ft_lstclear(&checker->stack_b, free);
	checker->bintree = ft_bintree_free(checker->bintree);
	if (checker->bintree)
		checker->bintree = ft_bintree_free(checker->bintree);
	if (checker->lst)
		ft_lstclear(&checker->lst, free);
}

void	print_error(char *error_msg, char *ansi_color_code)
{
	write(STDERR_FILENO, ansi_color_code, ft_strlen(ansi_color_code));
	ft_putendl_fd(error_msg, STDERR_FILENO);
	write(STDERR_FILENO, RESET, 4);
}

void	exit_failure(char *error_msg, t_checker *checker)
{
	if (error_msg)
		print_error(error_msg, RED);
	freeme(checker);
	exit(EXIT_FAILURE);
}

void	exit_success(t_checker *checker)
{
	freeme(checker);
	exit(EXIT_SUCCESS);
}

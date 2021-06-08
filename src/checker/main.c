/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:42:53 by miki              #+#    #+#             */
/*   Updated: 2021/06/08 23:32:39 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

char	stack_is_sorted(t_checker *checker)
{
	t_list	*tmp;

	if (checker->stack_b)
		return (0);
	else
	{
		tmp = checker->stack_a;
		while (tmp->next)
		{
			if (*(int *)tmp->content > *(int *)tmp->next->content)
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}

/*
** OK, so we get an unspecified number of arguments, each with numbers to be
** checked for adequacy and then put in stack a.
**
** OK, first I'll use numbuf to store each individual number in the arguments
** and convert them into integers. The numbuf has room for 11 bytes plus the
** nul byte to make space for the minus sign if needed.
**
	// //debug code
	// printf("SORTED STACK A:\n");
	// for (t_list *tmp = checker.stack_a; tmp; tmp = tmp->next)
	// {
	// 	printf("%d\n", *(int *)tmp->content);
	// }
	// printf("SORTED STACK B:\n");
	// for (t_list *tmp = checker.stack_b; tmp; tmp = tmp->next)
	// {
	// 	printf("%d\n", *(int *)tmp->content);
	// }
	// //debug code
*/

int	main(int argc, char **argv)
{
	t_checker	checker;

	ft_bzero(&checker, sizeof(t_checker));
	if (argc < 2 || argv[1][0] == '\0')
		exit_failure(NULL, &checker);
	generate_stacks(argv, &checker);
	get_instructions(&checker);
	sort(&checker);
	if (stack_is_sorted(&checker))
		printf(GRN"OK\n"RESET);
	else
		printf(RED"KO\n"RESET);
	exit_success(&checker);
}

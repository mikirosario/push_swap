/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:42:53 by miki              #+#    #+#             */
/*   Updated: 2021/05/12 22:55:26 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/*
** OK, so we get an unspecified number of arguments, each with numbers to be
** checked for adequacy and then put in stack a.
**
** OK, first I'll use numbuf to store each individual number in the arguments
** and convert them into integers. The numbuf has room for 11 bytes plus the
** nul byte to make space for the minus sign if needed.
*/

int	main(int argc, char **argv)
{
	t_checker	checker;

	ft_bzero(&checker, sizeof(t_checker));
	//No argument provided :p
	if (argc < 2 || argv[1][0] == '\0')
		exit_failure(NULL, &checker);
	generate_stacks(argv, &checker);
	get_instructions(&checker);
	sort(&checker);

	//debug code
	printf("SORTED STACK A:\n");
	for (t_list *tmp = checker.stack_a; tmp; tmp = tmp->next)
	{
		printf("%d\n", *(int *)tmp->content);
	}
	printf("SORTED STACK B:\n");
	for (t_list *tmp = checker.stack_b; tmp; tmp = tmp->next)
	{
		printf("%d\n", *(int *)tmp->content);
	}
	//debug code
	
	// //debug code//
	// t_list *tmp = checker.lst;
	// while(tmp)
	// {
	// 	printf("%s\n", (char *)tmp->content);
	// 	if (ft_str_match(tmp->content, INSTRUCTIONS, ':') == 0)
	// 		printf("BAD BUNNY, %s no existe\n", (char *)tmp->content);
	// 	else if (ft_str_match(tmp->content, INSTRUCTIONS, ':') == 1)
	// 		printf("GOOD BUNNY, %s existe\n", (char *)tmp->content);
	// 	else
	// 		printf("WTF BUNNY?\n");
	// 	tmp = tmp->next;
	// }
	// //debug code

	exit_success(&checker);
}
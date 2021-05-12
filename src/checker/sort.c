/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 20:08:26 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/12 20:12:01 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	sort_stack(t_checker *checker, char *instruction)
{
	if (!ft_strcmp(instruction, "sa"))
		sa_move(checker);
	else if (!ft_strcmp(instruction, "sb"))
		sb_move(checker);
	else if (!ft_strcmp(instruction, "ss"))
		ss_move(checker);
	else if (!ft_strcmp(instruction, "pa"))
		pa_move(checker);
	else if (!ft_strcmp(instruction, "pb"))
		pb_move(checker);
	else if (!ft_strcmp(instruction, "ra"))
		ra_move(checker);
	else if (!ft_strcmp(instruction, "rb"))
		rb_move(checker);
	else if (!ft_strcmp(instruction, "rr"))
		rr_move(checker);
	else if (!ft_strcmp(instruction, "rra"))
		rra_move(checker);
	else if (!ft_strcmp(instruction, "rrb"))
		rrb_move(checker);
	else if (!ft_strcmp(instruction, "rrr"))
		rrr_move(checker);
	else
		exit_failure("Error", checker);
	
	// //DEBUG CODE
	// printf("SORTED STACK A:\n");
	// for (t_list *tmp = checker->stack_a; tmp; tmp = tmp->next)
	// {
	// 	if (tmp->content)
	// 		printf("%d\n", *(int *)tmp->content);
	// }
	// printf("\nSORTED STACK B:\n");
	// for (t_list *tmp = checker->stack_b; tmp; tmp = tmp->next)
	// {
	// 	if (tmp->content)
	// 		printf("%d\n", *(int *)tmp->content);
	// }
	// printf("\n");
	// //DEBUG CODE
}

void	sort(t_checker *checker)
{
	t_list	*instruction;

	instruction = checker->lst;
	while (instruction)
	{
		sort_stack(checker, instruction->content);
		instruction = instruction->next;
	}
}

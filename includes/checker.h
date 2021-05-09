/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:07:56 by miki              #+#    #+#             */
/*   Updated: 2021/05/09 21:54:36 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "libft.h"
# include "ft_bintree.h"
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# define INSTRUCTIONS "sa:sb:ss:pa:pb:ra:rb:rr:rra:rrb:rrr"

typedef struct s_checker
{
	t_bstnode	*bintree;
	size_t		stack_size;
	int			**stack_a;
	int			**stack_b;
	t_list		*lst;
}				t_checker;

int	generate_stacks(char **argv, t_checker *checker);
int	exit_failure(char *error_msg, t_checker *checker);

/*
** Movements
*/

void	sa_move(t_checker *checker);

#endif

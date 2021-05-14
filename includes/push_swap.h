/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 21:56:06 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/14 22:07:12 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include "ft_bintree.h"
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# define INSTRUCTIONS "sa:sb:ss:pa:pb:ra:rb:rr:rra:rrb:rrr"

typedef struct s_pswap
{
	t_bstnode	*bintree;
	t_list		*stack_a;
	t_list		*stack_b;
	t_list		*lst;
}				t_pswap;

// void		exit_failure(char *error_msg, t_pswap *pswap);
// void		exit_success(t_pswap *pswap);
int			generate_stacks(char **argv, t_pswap *pswap);
// void		get_instructions(t_pswap *pswap);
// void		sort(t_pswap *pswap);

// /*
// ** Movements
// */

// void		sa_move(t_pswap *pswap);
// void		sb_move(t_pswap *pswap);
// void		ss_move(t_pswap *pswap);
// void		pa_move(t_pswap *pswap);
// void		pb_move(t_pswap *pswap);
// void		ra_move(t_pswap *pswap);
// void		rb_move(t_pswap *pswap);
// void		rr_move(t_pswap *pswap);
// void		rra_move(t_pswap *pswap);
// void		rrb_move(t_pswap *pswap);
// void		rrr_move(t_pswap *pswap);

#endif
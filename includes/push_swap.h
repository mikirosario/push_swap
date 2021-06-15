/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 21:56:06 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/15 20:08:16 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include "ft_bintree.h"
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# define INSTRUCTIONS "sa:sb:ss:pa:pb:ra:rb:rr:rra:rrb:rrr"

typedef struct s_mask
{
	int		*vector;
	size_t	start_index;
	size_t	end_index;
}				t_mask;

typedef struct s_sequence
{
	size_t	r_moves;
	size_t	rr_moves;
	size_t	r_carry_moves;
	size_t	rr_carry_moves;
}				t_sequence;

typedef struct s_contiguous
{
	int	top;
	int	middle;
	int	bottom;
}				t_contiguous;

typedef struct s_fastest_rotation
{
	size_t	rr_move;
	size_t	rrr_move;
	size_t	ra_move;
	size_t	rb_move;
	size_t	rra_move;
	size_t	rrb_move;
	size_t	total_moves;
}				t_fastest_rotation;

typedef struct s_swap_pairs
{
	t_contiguous	a_pair;
	t_contiguous	b_pair;
	t_sequence		a_moves;
	t_sequence		b_moves;
}				t_swap_pairs;

typedef struct s_merge_sequence
{
	t_sequence			stack_a;
	t_sequence			stack_b;
}				t_merge_sequence;

typedef struct s_stack
{
	t_mask	mask;
	t_list	*stack;
	size_t	numbers;
	int		first;
	int		second;
	int		penult;
	int		last;
	int		smallest;
	int		largest;
}				t_stack;

typedef struct s_pivot
{
	int		*range;
	size_t	range_size;
	int		pivot_b;
}				t_pivot;

typedef struct s_pbar
{
	size_t	len;
	char	bar[101];
	char	empty[101];
}				t_pbar;

typedef struct s_pswap
{
	t_pivot		pivot;
	t_stack		stack_a;
	t_stack		stack_b;
	t_pbar		pbar;
	t_list		*stack_a_clone;
	t_bstnode	*bintree;
	t_bstnode	**array_tree;
	t_list		*instruction;
	size_t		numbers;
	size_t		move_counter;
	size_t		test_range_size;
	size_t		best_range_size;
	size_t		best_move_sequence;
	int			smallest;
	int			largest;
	int			desired_pos;
}				t_pswap;

/*
** Cleanup
*/

void				exit_failure(char *error_msg, t_pswap *pswap);
void				exit_success(t_pswap *pswap);

/*
** Toolbox
*/

void				array_my_tree(t_pswap *pswap);
int					generate_stacks(char **argv, t_pswap *pswap);
int					generate_instructions(t_pswap *pswap);
void				generate_position_map(t_pswap *pswap);
void				display_progress_bar(t_pswap *pswap);
void				merge_sequence(t_pswap *pswap);
void				process_moves(t_pswap *pswap, t_fastest_rotation *fastest);
void				push_lowers(t_pswap *pswap);
t_list				*clone_stack(t_list *original_stack);
t_list				*lst_reset(t_list *list);
void				get_relevant_numbers(t_pswap *pswap);
void				print_instructions(t_pswap *pswap);
t_fastest_rotation	find_fastest_double_rotate_solution(t_sequence *stack_a, \
					t_sequence *stack_b);

/*
** Solvers
*/

void				three_numbers(t_pswap *pswap);
void				six_numbers(t_pswap *pswap);
void				many_numbers(t_pswap *pswap);

/*
** Sort Conditions
*/

char				is_ordered(t_pswap *pswap);
int					are_contiguous(t_pswap *pswap, int smaller, int larger);
int					stack_a_is_sequenced(t_pswap *pswap, t_stack *stack);
int					stack_b_is_sequenced(t_pswap *pswap, t_stack *stack);

/*
** Movements
*/

void				sa_move(t_pswap *pswap);
void				sb_move(t_pswap *pswap);
void				ss_move(t_pswap *pswap);
void				pa_move(t_pswap *pswap);
void				pb_move(t_pswap *pswap);
void				ra_move(t_pswap *pswap);
void				rb_move(t_pswap *pswap);
void				rr_move(t_pswap *pswap);
void				rra_move(t_pswap *pswap);
void				rrb_move(t_pswap *pswap);
void				rrr_move(t_pswap *pswap);
void				sort_rotate_stack_a(t_pswap *pswap);
void				sequence_stacks(t_pswap *pswap);
void				add_move_to_list(t_pswap *pswap, char *move);

#endif

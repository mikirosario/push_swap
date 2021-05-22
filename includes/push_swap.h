/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 21:56:06 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/22 22:21:36 by mrosario         ###   ########.fr       */
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
# define ARRAY_BUF 1

typedef struct	s_vector
{
	int		*start;
	int		*index;
	int		*end;
	int		(*realloc)(struct s_vector *);
	int		(*add)(struct s_vector *, int); //add value pointed to by void ptr to array, realloc if needed
	int		(*rem)(struct s_vector *, int *); //remove array value pointed to by void ptr from array, do nothing if addr not part of array
	int		(*del)(struct s_vector **); // point to arr_del, delete array
	size_t	allocated_mem;
	size_t	len;
}				t_vector;

typedef struct	s_mask
{
	int		*vector;
	size_t	start_index;
}				t_mask;

typedef struct	s_relevant
{
	int	a_first;
	int	a_second;
	int	a_penult;
	int	a_last;
	int	b_first;
	int	b_second;
	int	b_penult;
	int b_last;
}				t_relevant;


typedef struct s_pswap
{
	t_mask		mask_a;
	t_mask		mask_b;
	t_relevant	num;
	t_bstnode	*bintree;
	t_list		*stack_a;
	t_list		*stack_b;
	t_list		*lst;
	//int			*mask_a;
	//int			*mask_b;
	size_t		numbers;
	size_t		stack_a_numbers;
	size_t		stack_b_numbers;
	int			desired_pos;
}				t_pswap;

// void		exit_failure(char *error_msg, t_pswap *pswap);
// void		exit_success(t_pswap *pswap);
int			generate_stacks(char **argv, t_pswap *pswap);
int			generate_instructions(t_pswap *pswap);
void		generate_position_map(t_pswap *pswap);
void		exit_failure(char *error_msg, t_pswap *pswap);
void		exit_success(t_pswap *pswap);

int	are_contiguous(t_pswap *pswap, int smaller, int larger);
int	is_sorted(t_list *stack);
int should_swap_stack_a(t_pswap *pswap);
int	should_rotate_stack_a(t_pswap *pswap);
void	rotate_stack(t_pswap *pswap, t_list *stack);
//int	first_pair_ordered(t_list *stack);

/*
** Move to libft
*/

t_vector	*vector_new(void);

/*
** SORT CONDITIONS
*/

char	is_ordered(t_pswap *pswap);
void	three_numbers(t_pswap *pswap);
void	five_numbers(t_pswap *pswap);
int		equal_offsets(t_pswap *pswap);
int		push_down(t_pswap *pswap);
// void		get_instructions(t_pswap *pswap);
// void		sort(t_pswap *pswap);

/*
** Movements
*/

void		sa_move(t_pswap *pswap);
void		sb_move(t_pswap *pswap);
void		ss_move(t_pswap *pswap);
void		pa_move(t_pswap *pswap);
void		pb_move(t_pswap *pswap);
void		ra_move(t_pswap *pswap);
void		rb_move(t_pswap *pswap);
void		rr_move(t_pswap *pswap);
void		rra_move(t_pswap *pswap);
void		rrb_move(t_pswap *pswap);
void		rrr_move(t_pswap *pswap);
void		add_move_to_list(t_pswap *pswap, char *move);

#endif
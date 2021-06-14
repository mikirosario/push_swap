/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_fastest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:13:24 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/14 21:02:42 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** This function submits an initial proposal for an r_move or rotate move set.
**
** It will propose the shortest number of rr_moves and/or ra_moves and/or
** rb_moves to get both target numbers to the top of their respective stacks.
** First we must identify who is the tortoise and who is the hare, that is, who
** will get to the top slowest and who will get there fastest with the rotate
** moves, the number in stack_a or the number in stack_b. Depending on the
** answer we fashion a move 'proposal'. We use a special struct for that.
**
** First we zero the proposal struct.
**
** Then we ask if stack_a is the tortoise by asking if a's r_moves are greater
** than b's r_moves. If stack_a is the tortoise then that makes stack_b the hare
** so the total rr_moves will be the hare's (b's) r_moves. These double moves
** count as a single move, so we subtract them from the tortoise's total. The
** remaining tortoise moves are independent, so we make them ra_moves.
**
** The same logic holds if stack_b is the tortoise.
**
** If both numbers will arrive at the same time (lucky!), it doesn't matter
** where they are calculated, as the tortoise - hare subtraction will return 0
** for 0 additional independent moves.
**
** Then we tally up the moves for convenience and send back the proposal.
*/

t_fastest_rotation	get_rotate_moves(size_t a_moves, size_t b_moves)
{
	t_fastest_rotation	proposal;

	ft_bzero(&proposal, sizeof(t_fastest_rotation));
	if (a_moves > b_moves)
	{
		proposal.rr_move = b_moves;
		proposal.ra_move = a_moves - b_moves;
	}
	else
	{
		proposal.rr_move = a_moves;
		proposal.rb_move = b_moves - a_moves;
	}
	proposal.total_moves = proposal.rr_move + \
	proposal.ra_move + proposal.rb_move;
	return (proposal);
}

/*
** This function is the same as get_rotate_moves, but looks at reverse_rotate
** moves instead.
*/

t_fastest_rotation	get_reverse_rotate_moves(size_t a_moves, size_t b_moves)
{
	t_fastest_rotation	proposal;

	ft_bzero(&proposal, sizeof(t_fastest_rotation));
	if (a_moves > b_moves)
	{
		proposal.rrr_move = b_moves;
		proposal.rra_move = a_moves - b_moves;
	}
	else
	{
		proposal.rrr_move = a_moves;
		proposal.rrb_move = b_moves - a_moves;
	}
	proposal.total_moves = proposal.rrr_move + \
	proposal.rra_move + proposal.rrb_move;
	return (proposal);
}

/*
** This function determines the preference of a stack for moving an integer to
** the top (without taking into consideration the other stack's feelings ;)).
** It will always prefer the least number of moves. If the rotate moves would
** be the same as the reverse rotate moves reverse rotate is preferred.
**
** For rotate-biased stacks, we return the character '<'. Otherwise, we return
** '>'.
*/

char	get_stack_preference(t_sequence *stack)
{
	if (stack->r_moves < stack->rr_moves)
		return ('<');
	else
		return ('>');
}

/*
** This function queries the number of moves needed to rotate the numbers in
** stack_a and stack_b to the top in OPPOSITE directions (for example, ra_move
** in one stack and rrb_move in the other).
**
** Sometimes the fastest independent path for one number is in the opposite
** direction as the fastest independent path for the other. In that case, we say
** they are 'DIVERGENT'. Otherwise, we say they are 'CONVERGENT'.
**
** If they are divergent, we're interested in knowing whether the divergent
** solution (the one where each number is rotated in the opposite direction,
** independently) is faster (has less moves) than the convergent one (the one
** where at least some of the moves are shared via rr_move or rrr_move).
**
** If they are convergent (they both prefer the same direction anyway), we don't
** need to check the divergent solution, so we just return the incumbent
** proposal. If they are divergent, however, we do check and return our own
** divergent proposal with the total moves tallied up at the end. If it turns
** out to be shorter than the convergent proposals, it will be favoured.
*/

t_fastest_rotation	get_divergent_moves(t_sequence *stack_a, \
					t_sequence *stack_b, t_fastest_rotation incumbent)
{
	t_fastest_rotation	proposal;
	char				stack_a_preference;
	char				stack_b_preference;

	ft_bzero(&proposal, sizeof(t_fastest_rotation));
	stack_a_preference = get_stack_preference(stack_a);
	stack_b_preference = get_stack_preference(stack_b);
	if (stack_a_preference == stack_b_preference)
		return (incumbent);
	if (stack_a_preference == '<')
	{
		proposal.ra_move = stack_a->r_moves;
		proposal.rrb_move = stack_b->rr_moves;
	}
	else
	{
		proposal.rra_move = stack_a->rr_moves;
		proposal.rb_move = stack_b->r_moves;
	}
	proposal.total_moves = proposal.ra_move + proposal.rb_move + \
	proposal.rra_move + proposal.rrb_move;
	return (proposal);
}

/*
** In this function we'll find the fastest solution to get a pair of numbers
** in stack_a and stack_b to the top of their respective stacks! We'll divide
** the numbers into two: the tortoise and the hare. The tortoise is the number
** that takes the longest to get to the top and the hare is the one that gets
** there quickest. So long as the numbers are moving in tandem, using rr_move or
** rrr_move, their movements count as single movements, so we want to remove
** all of the movements that count as single movements from the movement tally.
**
** Therefore: tortoise_moves - hare_moves = carry_moves (number of extra moves
** needed by the tortoise). If both numbers will get there in the same number
** of moves, it doesn't matter who is tortoise and who is hare as the
** subtraction will return carry_moves = 0 and the total moves will be just the
** sum of the joint moves.
**
** If two proposals have the same number of moves, the incumbent proposal will
** be preferred.
*/

t_fastest_rotation	find_fastest_double_rotate_solution(t_sequence *stack_a, \
t_sequence *stack_b)
{
	t_fastest_rotation	fastest;
	t_fastest_rotation	proposal;

	fastest = get_rotate_moves(stack_a->r_moves, stack_b->r_moves);
	proposal = get_reverse_rotate_moves(stack_a->rr_moves, stack_b->rr_moves);
	if (proposal.total_moves < fastest.total_moves)
		fastest = proposal;
	proposal = get_divergent_moves(stack_a, stack_b, fastest);
	if (proposal.total_moves < fastest.total_moves)
		fastest = proposal;
	return (fastest);
}

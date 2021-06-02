/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 08:58:35 by miki              #+#    #+#             */
/*   Updated: 2021/06/02 10:19:44 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** This function finds the number passed as num in the stack passed as stack and
** returns how far (how many hops) it is away from the top of the stack.
**
** As in sequence_stacks, moving from the top of the stack down is movement in
** the 'positive' direction, corresponding to the rotate move, so the number
** r_moves indicates the number of rotate moves needed to rotate the number to
** the top. The number of reverse rotate moves required for the same is given by
** stack->numbers - rotate_moves. We save those values in a t_sequence struct,
** also as we did in sequence_stacks.
**
** If the number is not in the stack, 0 is returned. Otherwise, 1 is returned.
*/

static int find_in_stack(t_stack *stack, t_sequence *sequence, int num)
{
	t_list	*stk;
	size_t	r_moves;

	r_moves = 0;
	stk = stack->stack;
	// //debug
	// if (num == 24)
	// {
	// 	printf("LO STACK B\n");
	// 	for(t_list *tmp = stack->stack; tmp; tmp = tmp->next)
	// 		printf("%d\n", *(int *)tmp->content);
	// }
	// //debug

	while (stk)
	{
		if (*(int *)stk->content == num)
		{
			sequence->r_moves = r_moves;
			sequence->rr_moves = stack->numbers - r_moves;
			return (1);
		}
		stk = stk->next;
		r_moves++;
	}
	return (0);
}

/*
** This function retrieves the numbers contiguous to the integer passed as num in
** the binary tree and saves the result in the struct passed as cont. The
** integer passed as num is considered to be the 'middle' value. Nothing fancy
** here. I converted my binary tree into an array for this. xD Just fine the
** number in the array, then check the preceding and following numbers.
**
** Because of the way stack rotation works, the smallest and largest numbers in
** the series are effectively contiguous as well. This is a special case. So if
** we detect that num is the smallest, its top number is going to be the
** largest, and if we detect that num is the largest, its bottom number is going
** to be the smallest. If the array index is 0 it is the smallest number and if
** it is numbers - 1 it is the largest, as the array is ordered.
*/

void	get_contiguous_numbers(t_pswap *pswap, t_contiguous *cont, int num)
{
	size_t	i;

	cont->middle = num;
	i = 0;
	while (i < pswap->numbers && (pswap->array_tree[i])->data != (long int)num)
		i++;
	if (i == 0)
		cont->top = pswap->largest;
	else
		cont->top = (int)(pswap->array_tree[i - 1])->data;
	if (i == pswap->numbers - 1)
		cont->bottom = pswap->smallest;
	else
		cont->bottom = (int)(pswap->array_tree[i + 1])->data;
}

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
	t_fastest_rotation proposal;

	ft_bzero(&proposal, sizeof(t_fastest_rotation));
	if (a_moves > b_moves) //stack_a is the tortoise
	{
		proposal.rr_move = b_moves;
		proposal.ra_move = a_moves - b_moves;
	}
	else //stack_b is the tortoise, or it doesn't matter
	{
		proposal.rr_move = a_moves;
		proposal.rb_move = b_moves - a_moves;
	}
	proposal.total_moves = proposal.rr_move + proposal.ra_move + proposal.rb_move;
	return (proposal);
}

/*
** This function is the same as get_rotate_moves, but looks at reverse_rotate
** moves instead.
*/

t_fastest_rotation	get_reverse_rotate_moves(size_t a_moves, size_t b_moves)
{
	t_fastest_rotation proposal;

	ft_bzero(&proposal, sizeof(t_fastest_rotation));
	if (a_moves > b_moves) //stack_a is the tortoise
	{
		proposal.rrr_move = b_moves;
		proposal.rra_move = a_moves - b_moves;
	}
	else //stack_b is the tortoise, or it doesn't matter
	{
		proposal.rrr_move = a_moves;
		proposal.rrb_move = b_moves - a_moves;
	}
	proposal.total_moves = proposal.rrr_move + proposal.rra_move + proposal.rrb_move;
	return (proposal);
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

t_fastest_rotation		get_divergent_moves(t_sequence *stack_a, t_sequence *stack_b, t_fastest_rotation incumbent)
{
	t_fastest_rotation	proposal;
	char				stack_a_preference;
	char				stack_b_preference;

	ft_bzero(&proposal, sizeof(t_fastest_rotation));
	if (stack_a->r_moves < stack_a->rr_moves)
		stack_a_preference = '<';
	else
		stack_a_preference = '>';
	if (stack_b->r_moves < stack_b->rr_moves)
		stack_b_preference = '<';
	else
		stack_b_preference = '>';
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
	proposal.total_moves = proposal.ra_move + proposal.rb_move + proposal.rra_move + proposal.rrb_move;
	return (proposal);
	//return (stack_a_preference != stack_b_preference)
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
**

*/
t_fastest_rotation	find_fastest_double_rotate_solution(t_sequence *stack_a, t_sequence *stack_b)
{
	t_fastest_rotation	fastest;
	t_fastest_rotation	proposal;

//rotate moves
	fastest = get_rotate_moves(stack_a->r_moves, stack_b->r_moves);
//reverse rotate moves
	proposal = get_reverse_rotate_moves(stack_a->rr_moves, stack_b->rr_moves);
	if (proposal.total_moves < fastest.total_moves)
		fastest = proposal;
//divergent rotate moves
	proposal = get_divergent_moves(stack_a, stack_b, fastest);
	if (proposal.total_moves < fastest.total_moves)
		fastest = proposal;
	return (fastest);
}

/*
** So the game here is very similar to sequence_stacks, only this time instead
** of two unsequenced pairs, one in stack_a and one in stack_b, that we want to
** move to the top to double-swap, we have a single pair of contiguous numbers,
** one in stack_a and one in stack_b, and we want to move them to the top to
** push the one in stack_b into sequence in stack_a.
**
** We want to insert the contiguous pair that requires the lowest number of
** moves to position at the top. So we need to calculate the optimal moves for
** each contiguous pair and replace them with more optimal moves as they are
** found.
**
** The first question to ask is what is a contiguous pair and where is the
** nearest one? The function are_contiguous will check whether two numbers are
** contiguous using the binary tree, but in this case what I really want is a
** function that will return the contiguous numbers of any number in the tree.
** In a binary tree, the contiguous values to any node are the highest value
** in the negative direction (usually left) and the lowest value in the positive
** direction (usually right). You can get to either value by just going left
** from the root and then selecting all the right children until the end, and
** going right from the root and selecting all the left children until the end.
** So I'm going to do it that way. :)
**
** First I take the first member of stack_a and query get_contiguous_numbers for
** its contiguous values in the series, which should be saved in the contiguous
** struct.
**
** Now that we know what they are, we can try to find them in stack_b. For each
** contiguous pair, we will then ask for the most efficient solution to get the
** value in stack_b in the appropriate contiguous position in stack_a. This
** means rotating one or both stacks until the pair are at the top and doing
** pa_move. If we can't find a value in stack_b, we know it must be in stack_a,
** and since merge_sort is triggered after sequence_stacks, we also know it must
** already be sequenced. So we ignore it.
**
** Here is where things get tricky. Depending on where the two values are in
** both stacks relative to each other, it may be more convenient for either of
** them to 'double rotate' to save moves, even if it means going the long way
** 'round. The logic is the same as in sequence stacks. The find_in_stack
** function will tell us how many rotate and reverse rotate moves we'd need to
** rotate the contiguous number to the top. The number of iterations in the
** stack_a while is likewise equal to the number of r_moves we would need to
** bring the current stack_a number to the top of stack a. So we'll use
** sequence_a.r_moves as a counter. As with stack_b, we use
** stack->numbers - r_moves to calculate rr_moves. We'll only bother doing this
** if we find a contiguous value in stack_b, though.
**
** Now that we have all that, we need to know the carry_values again. That is,
** if we rotate both numbers together in either direction, how many extra moves
** will the straggler need to make it to the top.
**
** We have three options. The first two are CONVERGENT (both stacks move in the
** same direction), while the final one is DIVERGENT (both stacks move in
** opposite directions).
**
** 1.	Move the pair together in the rr_move direction, then finish with
**		ra/rb_moves as needed.
** 2.	Move the pair together in the rrr_move direction, then finish with
**		rra/rrb moves as needed.
** 3.	Move the pair independently in opposite directions.
**
** Least moves wins. :) If one of the three options results in less moves, we
** favour it.
**
** //CALCULATING CONVERGENT MOVES\\
** For the joint moves, we just need to figure out who gets to the top first.
** That will naturally be the one with the fewest rotate or reverse rotate
** moves. We'll call that one the "hare". The other one is the "straggler" or
** the "tortoise". Since the hare is faster, the tortoise always moves with the
** hare. While the hare is moving, the tortoise will also be moving. Therefore
** the hare's moves always reflect the number of joint moves.
**
** Once we know how many joint moves there are, we need to figure out how many
** additional moves the straggler must make after the hare reaches the top. To
** get that number we merely subtract the hare's moves from the tortoise's
** moves. The result is the number of moves the tortoise will have to make
** independently after the hare stops.
**
** To get the total number of moves we subtract the hare's total moves from the
** tortoise's total moves (this gives us carry_moves), and then add that to the
** hare one's total moves.
**
** //CALCULATING DIVERGENT MOVES\\
** For divergent moves, we just sum them together. Easy as that. :)
**
** Note: Kind of confusingly, in t_sequence r_moves stands for rotate, and
** rr_moves stands for reverse rotate. In t_fastest_rotation, rr_move is just
** number of joint rotates and rrr_move is number of joint reverse rotates...
** really need to change that nomenclature. :p
*/

void	merge_sequence(t_pswap *pswap)
{
	t_list				*stack_a;
	t_contiguous		contiguous;
	t_merge_sequence	sequence;
	t_fastest_rotation	fastest;
	t_fastest_rotation	proposal;
	size_t				x;

	stack_a = pswap->stack_a.stack;
	ft_bzero (&sequence, sizeof(t_merge_sequence));
	ft_memset(&fastest, INT_MAX, sizeof(t_fastest_rotation));
	x = 0;
	while (stack_a)
	{
		get_contiguous_numbers(pswap, &contiguous, *(int *)stack_a->content);
		//contiguous top
		if (find_in_stack(&pswap->stack_b, &sequence.stack_b, contiguous.top))
		{
			sequence.stack_a.r_moves = x;
			sequence.stack_a.rr_moves = pswap->stack_a.numbers - sequence.stack_a.r_moves;
			proposal = find_fastest_double_rotate_solution(&sequence.stack_a, &sequence.stack_b);
			if (fastest.total_moves > proposal.total_moves)
				fastest = proposal;
		}
		//contiguous bottom
		if (find_in_stack(&pswap->stack_b, &sequence.stack_b, contiguous.bottom))
		{
			sequence.stack_a.r_moves = x + 1;
			sequence.stack_a.rr_moves = pswap->stack_a.numbers - sequence.stack_a.r_moves;
			proposal = find_fastest_double_rotate_solution(&sequence.stack_a, &sequence.stack_b);
			if (fastest.total_moves > proposal.total_moves)
				fastest = proposal;
		}
		stack_a = stack_a->next;

		x++;
	}

	void (*move[6])(t_pswap *);
	size_t	i;

	move[0] = rr_move;
	move[1] = rrr_move;
	move[2] = ra_move;
	move[3] = rb_move;
	move[4] = rra_move;
	move[5] = rrb_move;
	i = 0;

	while (i < 6)
	{
		while (((size_t *)(&fastest))[i]--)
			move[i](pswap);
		i++;
	}

	// //debugcode
	// get_relevant_numbers(pswap);
	// //debug code
	pa_move(pswap);

		// //debug code
		// print_instructions(pswap);
		// //debug code
	// //debug code
	// printf("---------MARRIAGE PROPOSAL---------\n");
	// for (size_t i = 0; i < 6; i++)
	// {
	// 	printf("%zu\n", ((size_t *)(&fastest))[i]);
	// }
	// printf("%zu\n", fastest.total_moves);
	// //debug code
}

void	merge_sequence_b(t_pswap *pswap)
{
	t_list				*stack_b;
	t_contiguous		contiguous;
	t_merge_sequence	sequence;
	t_fastest_rotation	fastest;
	t_fastest_rotation	proposal;
	size_t				x;

	stack_b = pswap->stack_a.stack;
	ft_bzero (&sequence, sizeof(t_merge_sequence));
	ft_memset(&fastest, INT_MAX, sizeof(t_fastest_rotation));
	x = 0;
	while (stack_b)
	{
		// //debug
		// get_relevant_numbers(pswap);
		// //debug
		get_contiguous_numbers(pswap, &contiguous, *(int *)stack_b->content);
		//contiguous top
		if (find_in_stack(&pswap->stack_a, &sequence.stack_a, contiguous.top))
		{
			sequence.stack_b.r_moves = x;
			sequence.stack_b.rr_moves = pswap->stack_b.numbers - sequence.stack_b.r_moves;
			proposal = find_fastest_double_rotate_solution(&sequence.stack_a, &sequence.stack_b);
			if (fastest.total_moves > proposal.total_moves)
				fastest = proposal;
		}
		//contiguous bottom
		if (find_in_stack(&pswap->stack_a, &sequence.stack_a, contiguous.bottom))
		{
			sequence.stack_b.r_moves = x + 1;
			sequence.stack_b.rr_moves = pswap->stack_b.numbers - sequence.stack_b.r_moves;
			proposal = find_fastest_double_rotate_solution(&sequence.stack_a, &sequence.stack_b);
			if (fastest.total_moves > proposal.total_moves)
				fastest = proposal;
		}
		stack_b = stack_b->next;
		x++;
	}

	void (*move[6])(t_pswap *);
	size_t	i;

	move[0] = rr_move;
	move[1] = rrr_move;
	move[2] = ra_move;
	move[3] = rb_move;
	move[4] = rra_move;
	move[5] = rrb_move;
	i = 0;

	while (i < 6)
	{
		while (((size_t *)(&fastest))[i]--)
			move[i](pswap);
		i++;
	}

	// //debugcode
	// get_relevant_numbers(pswap);
	// //debug code
	pa_move(pswap);

	// //debug code
	// printf("---------MARRIAGE PROPOSAL---------\n");
	// for (size_t i = 0; i < 6; i++)
	// {
	// 	printf("%zu\n", ((size_t *)(&fastest))[i]);
	// }
	// printf("%zu\n", fastest.total_moves);
	// //debug code
}
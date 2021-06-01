/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence_stacks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 22:24:55 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/01 19:02:39 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**
*/

int	get_median_num(t_pswap *pswap)
{
	int	median_position;

	median_position = pswap->stack_a.numbers / 2;
	return ((int)(pswap->array_tree[median_position - 1])->data);
}

/*
** An unsequenced number pair is any descending pair of numbers except the
** smallest and largest. Incidentally, this means that largest/smallest pairs
** are unsequenced if they are *ascending*. :) The first member of the pair is
** passed as the integer anterior and the second is passed as the integer
** posterior.
*/

int	pair_is_sequenced(t_stack *stack, int anterior, int posterior)
{
	if (anterior > posterior && !(anterior == stack->largest && posterior == stack->smallest))
		return (0);
	return (1);
}

/*
** Identifies the next unsequenced pair from the top moving downwards in the
** stack. The distance from the top to the first member of the pair is counted.
** This corresponds to the r-distance, or distance in r-moves from the top. The
** distance in rr-moves is the inverse of the distance in r-moves, given by
** stack->numbers - r-moves.
**
** The r_moves and rr_moves from the next unsequenced pair to the top are saved
** in the struct to which the sequence pointer points. A pointer to the smallest
** of the two is also saved as the shortest path. If both paths are the same
** length, a pointer to NULL is saved. This function assumes there *are*
** unsequenced pairs in the stack and that the stack in question exists so DON'T
** use it unless it is behind a stack_is_sequenced query that returns false. It
** also assumes the sequence structure exists.
*/

void	find_next_unsequenced_pair(t_stack *stack, t_sequence *sequence)
{
	t_list *stk;
	size_t	i;

	stk = stack->stack;
	i = 0;
	while (stk->next)
	{
		if (!pair_is_sequenced(stack, *(int *)stk->content, *(int *)stk->next->content))
			break ;
		stk = stk->next;
		i++;
	}
	sequence->r_moves = i;
	sequence->rr_moves = stack->numbers - i;
}

/*
** This function determines how many extra individual moves will be needed for
** the pair in this stack when the other arrives at its destination.
*/
void	get_carry_moves(t_sequence *stack_a, t_sequence *stack_b)
{
	if (stack_a->r_moves < stack_b->r_moves)
	{
		stack_a->r_carry_moves = 0;
		stack_b->r_carry_moves = stack_b->r_moves - stack_a->r_moves;
	}
	else
	{
		stack_b->r_carry_moves = 0;
		stack_a->r_carry_moves = stack_a->r_moves - stack_b->r_moves;
	}
	if (stack_a->rr_moves < stack_b->rr_moves)
	{
		stack_a->rr_carry_moves = 0;
		stack_b->rr_carry_moves = stack_b->rr_moves - stack_a->rr_moves;
	}
	else
	{
		stack_b->rr_carry_moves = 0;
		stack_a->rr_carry_moves = stack_a->rr_moves - stack_b->rr_moves;
	}
}

/*
** This function finds the next pair of unsequenced numbers in a stack and moves
** them to the top as efficiently as possible. To get numbers to the top we
** ideally want to use double-rotates as much as possible. So say we have a
** situation like this:
**
** 	Stack_A		Stack_B
**	ra	3			5	rb
**	ra	7			6	rb
**	ra	2			9	rrb
**	ra	11			8	rrb
**	rra	1			10	rrb
**	rra	0			4	rrb
**
** What a mess!  We want to sequence move 9 and 8 to the top in Stack_B and 0
** and 1 to the top in Stack_A and sequence them. The shortest route for Stack_B
** is rb, while the shortest route for 2 and 1 is rra. So we'd get, for Stack_B,
** rb, rb, sb, and for Stack_A, rra, rra, sa. Six moves. But we could also
** submit Stack_B to Stack_A logic and do this: rrr, rrr, rrb, rrb, ss.
** Five moves. Same number of rotates, but now since we have both pairs in their
** positions at the same time, we can ss-swap them, so we get a free move.
**
** So you see the conundrum? ;p When you double-rotate and double-swap,
** sometimes it's more efficient to take the long way! The question is, when?
**
** Position arithmetic dictates that using rra, the 1 and 0 combination are 2
** positions away from the desired position, and using ra they are 4 positions
** away. Using rb, the 9 and 8 combination are also 2 positions away from the
** desired position while using rrb they are 4 positions away.
**
** Therefore, using rr, we can move the 9 and 8 to their desired position in 2
** moves, and 0 and 1 two moves towards their desired position 'for free', then
** we have 2 moves left over to move the 0 and 1 into their desired position, so
** rr, rr, ra, ra. Same number of moves as before. But we still get a free swap.
**
** So once we identify the nearest two pairs to the top in both stacks, the
** interesting datum here is, after we apply rr or rrr until one of them is in
** position, are the number of *remaining* r or rr moves for the pair in the
** other stack greater than the number of independent moves in the opposite
** direction it would have taken that pair to get to the same position? If they
** are, then it is more efficient to go independently. If NOT, it is ALWAYS
** more efficient to move them jointly in a single direction, EVEN if that means
** more total moves for one of the stacks! Because any moves taken jointly with
** the other stacks are essentially free moves.
**
** So, let's call these pairs 'hitchhikers'. ;) Imagine each pair of numbers has
** to take a conveyor belt to their destination, and for every movement they
** have to pay 1 fuel. But whenever one of them pays 1 fuel, the ENTIRE conveyor
** belt moves, dragging along anyone else on it! Good deal. Say they want to
** save money on fuel, rather than get to their destination quickly. Rather than
** paying to take the shortest route, they would rather hitch a ride on the
** conveyor belt going the long way if the trip is being paid for by another
** pair moving towards the same destination and, after that pair get off, the
** REMAINING fuel fees will be equal to or less than what they would have paid
** anyway. And since both pairs need to be swapped at their destination, it is
** ALWAYS more efficient to do it in one move between the two of them than in
** two moves at different times, right? Sharing is caring. :)
**
** So THAT's the efficiency check that I want here.
**
** STEP 1: Now that we know we have two unsequenced stacks, identify the NEXT
** unsequenced number pair from the top in each stack. Record the position of
** the first member of the pair relative to the top. :) The function
** find_next_unsequenced_pair will do just that, returning how many r_moves
** would be needed to rotate the identified pair to the top for swapping. The
** r_moves can be transformed into rr_moves with stack->numbers - r_moves.
**
** STEP 2: For each given pair we determine whether the shortest distance to the
** top is given by r_moves or rr_moves. If for both pairs they are the same, no
** problem at all, we just do STEP 4. If they are different, we go to step 3.
**
** STEP 3: If the shortest distance to the top are in opposite directions for
** the two different stacks, we compare how many individual moves each would be
** left with after all the joint moves are made for both r_moves and rr_moves.
** We call those leftover moves "carry_moves". Whichever direction would leave
** the lowest number of carry moves is preferred. If there is no difference,
** r_moves are preferred.
**
** STEP 4: Once we decide which way we want to go, we do as many rr_moves as
** needed to get at least one of the swappable unsequenced pairs to the top
** position, after which we run the remainder of moves for the other pair
** individually (as ra or rb moves). If one of the stacks already has an
** unsequenced pair in the top position, its r_moves and rr_moves will be 0, so
** the joint moves will be ignored and we will skip to the individual moves
** straight away. If both stacks already have a pair in the top position, we jump
** right to ss_move.
*/

/*
** This function finds the next unsequenced pair in the stack. An unsequenced
** is any pair of numbers when the top number is larger than the bottom number,
** except for the transition between stack->largest and stack->smallest, in
** which case the pair is unsequenced if the smallest is above the largest. So
** this has a special condition.
**
** I use the t_contiguous struct like in merge_sequence, though I won't use its
** middle integer here, just top and bottom. If the pair is unsequenced, the
** function returns 1. If it is already sequenced, the function returns 0.
**
** Once we find an unsequenced pair we enter
*/
static int unsequenced_pair(t_pswap *pswap, t_stack *stack, t_list *top, t_contiguous *pair)
{
	get_relevant_numbers(pswap);
	pair->top = *(int *)top->content;
	if (top->next == NULL)
		pair->bottom = stack->first;
	else
		pair->bottom = *(int *)top->next->content;
	//if (anterior > posterior && !(anterior == stack->largest && posterior == stack->smallest))
	if (pair->top > pair->bottom && !(pair->top == stack->largest && pair->bottom == stack->smallest))
		return (1);
	return 0;
}

void	double_sequence(t_pswap *pswap)
{
	t_list				*stack_a;
	t_list				*stack_b;
	t_fastest_rotation	fastest;
	t_fastest_rotation	proposal;
	t_swap_pairs		swap_pairs;

	ft_bzero(&swap_pairs, sizeof(t_swap_pairs));
	ft_memset(&fastest, INT_MAX, sizeof(t_fastest_rotation));
	stack_a = pswap->stack_a.stack;
	while (stack_a)
	{
		if (unsequenced_pair(pswap, &pswap->stack_a, stack_a, &swap_pairs.a_pair))
		{
			ft_bzero(&swap_pairs.b_moves, sizeof(t_sequence));
			stack_b = pswap->stack_b.stack;
			while (stack_b)
			{
				if (unsequenced_pair(pswap, &pswap->stack_b, stack_b, &swap_pairs.b_pair))
				{
					swap_pairs.a_moves.rr_moves = pswap->stack_a.numbers - swap_pairs.a_moves.r_moves;
					swap_pairs.b_moves.rr_moves = pswap->stack_b.numbers - swap_pairs.b_moves.r_moves;
					proposal = find_fastest_double_rotate_solution(&swap_pairs.a_moves, &swap_pairs.b_moves);
					if (fastest.total_moves > proposal.total_moves)
						fastest = proposal;
				}
				stack_b = stack_b->next;
				swap_pairs.b_moves.r_moves++;
			}
		}
		stack_a = stack_a->next;
		swap_pairs.a_moves.r_moves++;
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
	ss_move(pswap);


	// 	//debug code
	// printf("---------MARRIAGE PROPOSAL---------\n");
	// for (size_t i = 0; i < 6; i++)
	// {
	// 	printf("%zu\n", ((size_t *)(&fastest))[i]);
	// }
	// printf("%zu\n", fastest.total_moves);
	// //debug code
}

// void	double_sequence(t_pswap *pswap)
// {
// 	t_sequence	stack_a;
// 	t_sequence	stack_b;
// 	size_t		r_carry_moves;
// 	size_t		rr_carry_moves;

// 	get_relevant_numbers(pswap);
// 	find_next_unsequenced_pair(&pswap->stack_a, &stack_a);
// 	find_next_unsequenced_pair(&pswap->stack_b, &stack_b);
// 	get_carry_moves(&stack_a, &stack_b);
// 	if (!stack_b.r_carry_moves)
// 		r_carry_moves = stack_a.r_carry_moves;
// 	else
// 		r_carry_moves = stack_b.r_carry_moves;
// 	if (!stack_b.rr_carry_moves)
// 		rr_carry_moves = stack_a.rr_carry_moves;
// 	else
// 		rr_carry_moves = stack_b.rr_carry_moves;
// 	if (r_carry_moves <= rr_carry_moves)
// 	{
// 		while (stack_a.r_moves && stack_b.r_moves)
// 		{
// 			rr_move(pswap);
// 			stack_a.r_moves--;
// 			stack_b.r_moves--;
// 		}
// 		if (stack_a.r_moves)
// 			while (stack_a.r_moves--)
// 				ra_move(pswap);
// 		if (stack_b.r_moves)
// 			while (stack_b.r_moves--)
// 				rb_move(pswap);
// 	}
// 	else
// 	{
// 		while (stack_a.rr_moves && stack_b.rr_moves)
// 		{
// 			rrr_move(pswap);
// 			stack_a.rr_moves--;
// 			stack_b.rr_moves--;
// 		}
// 		if (stack_a.rr_moves)
// 			while(stack_a.rr_moves--)
// 				rra_move(pswap);
// 		if (stack_b.rr_moves)
// 			while(stack_b.rr_moves--)
// 				rrb_move(pswap);
// 	}
// 	ss_move(pswap);


// 	//if one or both pairs are equidistant from the top in both directions,
// 	//it doesn't matter which direction we choose. Go with the other's preferred
// 	//direction. If there is no preferred direction, go with r_move.



// }

void	sequence_stack_a(t_pswap *pswap)
{
	t_contiguous		pair;
	t_sequence			moves;
	t_fastest_rotation	proposal;
	t_fastest_rotation	fastest;
	t_list				*stack_a;

	ft_memset(&fastest, INT_MAX, sizeof(t_fastest_rotation));
	ft_bzero(&moves, sizeof(t_sequence));
	ft_bzero(&proposal, sizeof(t_fastest_rotation));
	//vvv--necesario?
	ft_bzero(&pair, sizeof(t_contiguous));
	//^^^--necesario?
	stack_a = pswap->stack_a.stack;
	get_relevant_numbers(pswap);
	while (stack_a)
	{
		if (unsequenced_pair(pswap, &pswap->stack_a, stack_a, &pair))
		{
			moves.rr_moves = pswap->stack_a.numbers - moves.r_moves;
			if (moves.r_moves < moves.rr_moves)
				proposal.ra_move = moves.r_moves;
			else
				proposal.rra_move = moves.rr_moves;
			proposal.total_moves = proposal.ra_move + proposal.rra_move;
			if (fastest.total_moves > proposal.total_moves)
				fastest = proposal;
		}
		stack_a = stack_a->next;
		moves.r_moves++;
	}
	if (fastest.ra_move)
		while(fastest.ra_move--)
			ra_move(pswap);
	else if (fastest.rra_move)
		while (fastest.rra_move--)
			rra_move(pswap);
	sa_move(pswap);


	// find_next_unsequenced_pair(&pswap->stack_a, &stack_a);
	// if (stack_a.r_moves <= stack_a.rr_moves)
	// {
	// 	while (stack_a.r_moves--)
	// 		ra_move(pswap);
	// }
	// else
	// {
	// 	while(stack_a.rr_moves--)
	// 		rra_move(pswap);
	// }
	// sa_move(pswap);
}

void	sequence_stack_b(t_pswap *pswap)
{
	t_sequence	stack_b;
	get_relevant_numbers(pswap);
	find_next_unsequenced_pair(&pswap->stack_b, &stack_b);
	if (stack_b.r_moves <= stack_b.rr_moves)
	{
		while (stack_b.r_moves--)
			rb_move(pswap);
	}
	else
	{
		while(stack_b.rr_moves--)
			rrb_move(pswap);
	}
	sb_move(pswap);
}



/*
**
*/

void	push_sequence(t_pswap *pswap)
{
	t_list			*stack_a;
	t_fastest_rotation	fastest;
	t_fastest_rotation	proposal;
	t_contiguous	a_pair;
	t_sequence		a_moves;

	stack_a = pswap->stack_a.stack;

	ft_bzero(&a_moves, sizeof(t_sequence));
	ft_bzero(&a_pair, sizeof(t_contiguous));
	ft_memset(&fastest, INT_MAX, sizeof(t_fastest_rotation));
	while (stack_a)
	{
		get_relevant_numbers(pswap);
		if (*(int *)stack_a->content == pswap->stack_a.smallest)
		{
			ft_bzero(&proposal, sizeof(t_fastest_rotation));
			a_moves.rr_moves = pswap->stack_a.numbers - a_moves.r_moves;
			if (a_moves.r_moves < a_moves.rr_moves)
				proposal.ra_move = a_moves.r_moves;
			else
				proposal.rra_move = a_moves.rr_moves;
			proposal.total_moves = proposal.ra_move + proposal.rra_move;
			if (fastest.total_moves > proposal.total_moves)
				fastest = proposal;
		}
		stack_a = stack_a->next;
		a_moves.r_moves++;
	}
	if (fastest.ra_move)
	{
		while (fastest.ra_move--)
			ra_move(pswap);
	}
	else if (fastest.rra_move)
		while (fastest.rra_move--)
			rra_move(pswap);
	pb_move(pswap);
}

/*
** To improve efficiency, this function will push only unsequenced top numbers
** in stack_a to stack_b, leaving stack_a sequenced after the pushes.
**
** We analyse all unsequenced pairs in the stack and find the shortest route to
** an unsequenced pair, then bring that pair's top number to the top of the
** stack and push it.
*/

void	push_unsequenced(t_pswap *pswap)
{
	t_list			*stack_a;
	t_fastest_rotation	fastest;
	t_fastest_rotation	proposal;
	t_contiguous	a_pair;
	t_sequence		a_moves;

	stack_a = pswap->stack_a.stack;

	ft_bzero(&a_moves, sizeof(t_sequence));
	ft_bzero(&a_pair, sizeof(t_contiguous));
	ft_memset(&fastest, INT_MAX, sizeof(t_fastest_rotation));
	while (stack_a)
	{
		if (unsequenced_pair(pswap, &pswap->stack_a, stack_a, &a_pair))
		{
			ft_bzero(&proposal, sizeof(t_fastest_rotation));
			a_moves.rr_moves = pswap->stack_a.numbers - a_moves.r_moves;
			if (a_moves.r_moves < a_moves.rr_moves)
				proposal.ra_move = a_moves.r_moves;
			else
				proposal.rra_move = a_moves.rr_moves;
			proposal.total_moves = proposal.ra_move + proposal.rra_move;
			if (fastest.total_moves > proposal.total_moves)
				fastest = proposal;
		}
		stack_a = stack_a->next;
		a_moves.r_moves++;
	}
	if (fastest.ra_move)
	{
		while (fastest.ra_move--)
			ra_move(pswap);
	}
	else if (fastest.rra_move)
		while (fastest.rra_move--)
			rra_move(pswap);
	pb_move(pswap);
	// get_relevant_numbers(pswap);
	// if (pswap->stack_b.first < pswap->stack_b.last)
	// 	rb_move(pswap);
}

/*
** This function uses the last two bits of the seq_flag to identify whether
** stack_a and stack_b are "sequenced". A stack is considered sequenced when
** it is in ascending order except for the transition between the smallest
** and largest number in the stack, considering that stacks loop, so the last
** number in a stack is next to the first number. For example, 1 2 0 is
** sequenced, because all numbers are in ascending order except for 2 (the
** largest) and 0 (the smallest). 1 0 2 is NOT sequenced because this is not
** true. So we separate each number series into the set of sequenced
** combinations and the set of unsequenced combinations.
**
** The algorithmic approach seeks first to sequence and then to order the
** stacks. This is to maximize the possibility of double-swap instructions (ss),
** since sequencing a stack means using swap. If I have to swap numbers in
** stack_a and stack_b, it is more instruction-efficient to bring the numbers I
** want to swap to the top of both stacks and swap them simultaneously with a
** single ss instruction, so this function will try to do that for as long as it
** can. We should sequence with roughly half of all numbers in the series in
** stack_b and the other half in stack_a.
**
** To achieve this we query whether each of the stacks are sequenced and bitwise
** OR both of their results into the seq_flag. The query will return 0 for not
** sequenced and 1 for sequenced. Empty stacks will be considered sequenced and
** return 1.
**
** Thus, the bitwise OR seq_flag values equate to the following information:
**
** Bin	Dec
** 00 == 00 - Neither stack is sequenced
** 01 == 01 - Only stack_a is sequenced
** 10 == 02 - Only stack_b is sequenced
** 11 == 03 - Both stacks are sequenced
**
** After both stacks are sequenced we can now merge_sort Stack_B back into
** Stack_A...
*/

void	push_lowers(t_pswap *pswap)
{
	t_list			*stack_a;
	size_t			x = 0;
	int				median = get_median_num(pswap);
	char			odd;

	while (!stack_is_sequenced(pswap, &pswap->stack_a))
	{
		stack_a = pswap->stack_a.stack;
		odd = (pswap->numbers % 2);

		while (stack_a)
		{
			if (*(int *)stack_a->content < median)
				pb_move(pswap);
			else
				ra_move(pswap);
			stack_a = stack_a->next;
			x++;
		}
	}
}

void	sequence_stacks(t_pswap *pswap)
{
	char	seq_flag;

	// size_t		i;
	// static char		stayout = 0;

	// //debug code
	// print_instructions(pswap);
	// //debug code

	// //push to stack b
	// if (!stayout)
	// {
	// 	i = pswap->numbers - (pswap->numbers / 2);
	// 	while (i--)
	// 		pb_move(pswap);
	// 	// while (!stack_is_sequenced(pswap, &pswap->stack_a))
	// 	// 	three_numbers(pswap);
	// 	stayout = 1;
	// }

	seq_flag = (char)(stack_is_sequenced(pswap, &pswap->stack_a) \
	 | (stack_b_is_sequenced(pswap, &pswap->stack_b) << 1));
	// if (seq_flag == 0)
	// 	double_sequence(pswap);
	// else if (seq_flag == 1)
	// 	sequence_stack_b(pswap);
	get_relevant_numbers(pswap);
	// if (stack_is_sequenced(pswap, &pswap->stack_b))
	// 	printf("MUMUª\n");¡
	//////NO PUEDDER SESEEEERRRR!!!"OIHUFHOPÑIDFIOH"
	if (pswap->numbers < 500 && (seq_flag == 2 || seq_flag == 0))
		while (!stack_is_sequenced(pswap, &pswap->stack_a))
			push_unsequenced(pswap);
	else if (pswap->numbers >= 500 && (pswap->stack_a.numbers > pswap->numbers / 5 && (seq_flag == 2 || seq_flag == 0)))
		while (pswap->stack_a.numbers > pswap->numbers / 5 && !(stack_is_sequenced(pswap, &pswap->stack_a)))
	 		pb_move(pswap); //pfffffffffffffffffffffffffffffffff!!!!!

	//mejor bajos
	//else if (seq_flag == 3 || seq_flag == 1)
	//mejor altos
	else
	{
		// //debug code
		// print_instructions(pswap);
		// //debug code
		//debug code
		while (pswap->stack_b.stack)
			merge_sequence(pswap);

		// exit_failure("STACKS SEQUENCED SUCCESSFULLY", pswap);
		// //debug code
		return ;
	}


	// //debug code
	// printf("SEQUENCING\n");
	// print_instructions(pswap);
	// 	printf("SEQ FLAG %d\n", seq_flag);
	// 	if (seq_flag == 0)
	// 		printf("Neither stack sequenced\n");
	// 	else if (seq_flag == 1)
	// 		printf("Stack B unsequenced\n");
	// 	else if (seq_flag == 2)
	// 		printf("Stack A unsequenced\n");
	// 	else if (seq_flag == 3)
	// 		printf("Both stacks are sequenced\n");
	// //debug code
}

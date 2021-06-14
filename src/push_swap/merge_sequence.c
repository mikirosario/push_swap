/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 08:58:35 by miki              #+#    #+#             */
/*   Updated: 2021/06/14 20:51:54 by mrosario         ###   ########.fr       */
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

static int	find_in_stack(t_stack *stack, t_sequence *sequence, int num)
{
	t_list	*stk;
	size_t	r_moves;

	r_moves = 0;
	stk = stack->stack;
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
** This function checks stack_b for the contiguous numbers of the integer in
** stack_a at position x. If either the top or bottom contiguous number is found
** in stack_b, the number of moves to get that integer (in the case of the top
** number) or the integer below it (in the case of a bottom number) to the top
** of the stack is saved to the sequence struct. The find_in_struct function
** does this for stack_b. For stack_a, the number of rotate moves is equal to
** the position of the integer in the stack, and the number of reverse rotate
** moves is equal to the number of integers in the stack minus the number of
** rotate moves.
**
** These data are then used to generate a proposal. If the proposal has less
** moves than the existing fastest proposal, it replaces the existing fastest
** proposal. See merge_sequence description for more details.
*/

void	update_fastest(t_pswap *pswap, t_contiguous *contiguous, \
t_fastest_rotation *fastest, size_t x)
{
	t_merge_sequence	sequence;
	t_fastest_rotation	proposal;

	ft_bzero(&sequence, sizeof(t_merge_sequence));
	if (find_in_stack(&pswap->stack_b, &sequence.stack_b, contiguous->top))
	{
		sequence.stack_a.r_moves = x;
		sequence.stack_a.rr_moves = \
		pswap->stack_a.numbers - sequence.stack_a.r_moves;
		proposal = find_fastest_double_rotate_solution(&sequence.stack_a, \
		&sequence.stack_b);
		if (fastest->total_moves > proposal.total_moves)
			*fastest = proposal;
	}
	if (find_in_stack(&pswap->stack_b, &sequence.stack_b, contiguous->bottom))
	{
		sequence.stack_a.r_moves = x + 1;
		sequence.stack_a.rr_moves = \
		pswap->stack_a.numbers - sequence.stack_a.r_moves;
		proposal = find_fastest_double_rotate_solution(&sequence.stack_a, \
		&sequence.stack_b);
		if (fastest->total_moves > proposal.total_moves)
			*fastest = proposal;
	}
}

/*
** So the game here is that we ideally want find the two contiguous integers
** in stack_a and stack_b that we can combine in stack_a with the least number
** moves, taking into account that we can save moves by double-rotating before
** pushing to stack_a.
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
** I create an ordered ascending array pointing to the tree integers at the
** beginning of the program so I use that to easily find the contiguous integers
** of any integer in the series.
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
** and so we ignore it.
**
** Here is where things get tricky. Depending on where the two values are in
** both stacks relative to each other, it may be more convenient for either of
** them to 'double rotate' to save moves, even if it means going the long way
** 'round. The find_in_stack function will tell us how many rotate and reverse
** rotate moves we'd need to rotate the contiguous numbers to the top of their
** stacks and save the result in sequence.stack_a and sequence.stack_b,
** respectively.
**
** The number of iterations in the stack_a while is equal to the number of
** normal rotates (r_moves) we would need to bring the current stack_a number
** to the top of stack_a becaue we iterate through stack_a from the top down.
** So sequence_a.r_moves is equal to our counter. If the contiguous pair in
** stack_b is a 'top', since pushing it to stack_a will put it on top of the
** partner, we want both of them at the top of the stack. If it is a 'bottom',
** however, we want the integer below the one in stack_a on the top, so we pass
** x + 1 as the integer we want to raise to the top. :)
**
** We then derive the number of reverse rotate moves from the number of rotate
** moves by subtracting the number of rotate moves from the total number of
** integers in the stack.
**
** The function find_in_stack does this for stack_b too.
**
** Now that we have all that, we need to know the carry_values. That is, if we
** rotate both numbers together in either direction and one of them reaches the
** top first, how many extra individual moves will the straggler need to make it
** to the top?
**
** In terms of which solution we decide is best to get the two numbers to the
** top of their stacks, we have three options.
**
** The first two are CONVERGENT (both stacks move in the same direction), while
** the final one is DIVERGENT (both stacks move in opposite directions). Here
** they are:
**
** 1.	Move the pair together in the rr_move direction, then finish with
**		ra/rb_moves as needed.
** 2.	Move the pair together in the rrr_move direction, then finish with
**		rra/rrb moves as needed.
** 3.	Move the pair independently in opposite directions.
**
** We calculate how many total moves result from each version.
**
** Least moves wins. :) If one of the three options results in less moves, we
** favour it. That is what find_fastest_double_rotation does.
**
** So the get_proposal function is passed the size_t index x, which is the
** number from the top of the current stack_a integer being analysed and so
** equivalent to the r_moves needed to bring that integer to the top, and a
** pointer to the sequence struct, which contains the r_moves and rr_moves to
** get the contiguous integer in stack_b to the top, and returns a PROPOSAL. The
** proposal contains the most efficient move plan for a given pair of contiguous
** numbers.
**
** We create a proposal for the top contiguous number and the bottom contiguous
** number. The highest and lowest integer in the series are considered
** contiguous. If we want to insert the bottom contiguous number, since it needs
** to go BELOW the integer in stack_a when it is pushed, the integer we want to
** bring to the top is actually the one BELOW the integer being analysed, so
** that the integer at the top of stack_b will be pushed on top of it and
** beneath the contiguous integer in stack_a. So we pass x + 1. No overflow risk
** because the number is just used to determine rotate moves, and it's circular.
**
** We continue running down the list of numbers in stack_a and generate proposal
** for every contiguous pair. When we get a new proposal, we compare it to the
** existing fastest proposal. If it is better (less moves), then we replace the
** old fastest proposal with the new fastest proposal. Otherwise it is
** discarded.
**
** The fastest proposal struct variables are initialized at SIZE_MAX so any
** initial proposal that is not a literal overflow will be better. Actually,
** they're initialized to INT_MAX, because memset wants an INT_MAX. But if I
** had taken this a bit more seriously and bothered to create another memset,
** they would TOTALLY be initialized to SIZE_MAX. xD Anyway, they're
** initialized to a Very Large Number(tm). ;)
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
	t_fastest_rotation	fastest;
	size_t				x;

	stack_a = pswap->stack_a.stack;
	ft_memset(&fastest, INT_MAX, sizeof(t_fastest_rotation));
	x = 0;
	while (stack_a)
	{
		get_contiguous_numbers(pswap, &contiguous, *(int *)stack_a->content);
		update_fastest(pswap, &contiguous, &fastest, x);
		stack_a = stack_a->next;
		x++;
	}
	process_moves(pswap, &fastest);
	pa_move(pswap);
}

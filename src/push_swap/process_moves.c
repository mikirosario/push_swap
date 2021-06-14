/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 16:50:05 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/14 17:15:54 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** This function is a bit tricksy, but it basically just executes all the moves
** in the fastest struct. It creates an array of six function pointers to point
** to the move functions referenced in the fastest struct, in order of their
** location in memory in the struct (this is important). The functions are all
** void, so these are pointers to void functions, and they all take a single
** t_swap pointer as an argument.
**
** The pointers are assigned to move functions in the same order as they appear
** in memory in the fastest struct.
**
** Then we just set an index to 0 and we treat the fastest struct as if it were
** itself an array of 6 size_t variables because... in fact, it IS an array of
** 6 size_t variables (actually 7, but we don't care about the last one). In the
** funky while I'm basically just telling the compiler, hey, I know this may
** seem strange because fastest is a struct of type t_fastest_rotation, but just
** trust me: dereference fastest as if it were a pointer to a size_t variable in
** an array of size_t variables (cast to size_t * and dereference with [i]).
**
** We then subtract 1 from the variable we dereference. Why? Because every
** variable in the fastest struct tells us how many times we need to execute a
** move, and the moves are in the same order we put them in in our array. So
** every variable in the fastest struct is effectively a move counter for the
** corresponding move, and we treat it as such. We subtract 1 from each move
** counter until we reach 0, and every time we subtract 1, we execute the
** corresponding move function.
**
** Since the moves in the pointer array are in the same order as in the struct,
** and in both cases start with index 0, i in the fastest struct will point to
** the move counter and i in the move array will point to its move function.
**
** When we reach 0, we increment i to analyse the next move/move counter tandem.
**
** We do this for all the moves. I realize this isn't the most elegant,
** easy-to-read way to do this, but it is literally the first thing I thought of
** and I've kind of grown fond of it. And hey: function pointer array! xD
*/

void	process_moves(t_pswap *pswap, t_fastest_rotation *fastest)
{
	void	(*move[6])(t_pswap *);
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
		while (((size_t *)(fastest))[i]--)
			move[i](pswap);
		i++;
	}
}

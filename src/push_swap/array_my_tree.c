/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_my_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 20:03:24 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/15 20:05:37 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** This does an in_order_traversal of the red-black binary tree, where for every
** number in ascending order of appearance we can 'do something'. In this case,
** we save its address in a sequenced array called array_tree for easy access.
*/

static void	in_order_traversal(t_pswap *pswap, t_bstnode *root)
{
	if (root != NULL)
	{
		in_order_traversal(pswap, root->left);
		pswap->array_tree[pswap->desired_pos++] = root;
		in_order_traversal(pswap, root->right);
	}
}

/*
** Sometimes you just REALLY want to make that binary tree you were using into
** an array. Amirite? For those times, in this program, there is this function.
** Best of both worlds, I always say. Or maybe I've just had enough of misuing
** binary trees in expensive calculations for the sake of practice. xD
**
** So I'm going to create an array of bst_node pointers. Let's get cracking!
*/

void	array_my_tree(t_pswap *pswap)
{
	pswap->array_tree = ft_calloc(pswap->numbers, sizeof(t_bstnode *));
	pswap->desired_pos = 0;
	in_order_traversal(pswap, pswap->bintree);
}

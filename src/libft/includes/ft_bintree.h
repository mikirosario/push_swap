/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 05:41:44 by miki              #+#    #+#             */
/*   Updated: 2021/04/10 06:57:37 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BINTREE_H
# define FT_BINTREE_H

# define BINTREE_MAX_DATA 4611686018427387903
# define BINTREE_MIN_DATA -4611686018427387904

/*
** Although I use long long int for the data segment, I actually sequester a
** single bit from it to store btree color data. So the storage limit is only
** 4611686018427387903 in positive integers and 4611686018427387904 in
** negatives. I still don't know how to say that number out loud, so should be
** long enough for most purposes. ;) Since our struct is going to be padded in
** 8-byte tranches anyway, because of the pointers, we might as well get as much
** bang for our byte as we can. ;) BINTREE_MAX_DATA and BINTREE_MIN_DATA define
** the respective maximum and minimum integers that can be held inside a binary
** tree node. The binary tree add function uses them to police input.
*/

typedef struct s_bstnode
{
	struct s_bstnode	*parent;
	struct s_bstnode	*left;
	struct s_bstnode	*right;
	long long int 		data : (sizeof(long long int) * __CHAR_BIT__) - 1;
	unsigned char		color : 1;
}				t_bstnode;

typedef struct s_bsttermcaps
{
	char	termbuf[2048];
	char	capbuf[2048];
	char	*cur_mov;
	char	*scroll_up;
}				t_bsttermcaps;

/*
** I'd REALLY rather do this by making tcaps and wsize globals in the
** ft_bintree_print scope, and just passing level, div and hpos as unstructured
** local variables, but 42 School Norm bans globals (and bans structs from being
** declared in .c), so then I couldn't compile my lib for school projects. :( So
** I did this instead.
**
** Since using the bstprint struct put me over the 4 argument limit for a
** function, also per 42 School Norm, I made all the variables into a struct
** too. They need their own struct, because I need to copy them from function to
** function and operate on them independently, not just address a single
** instance of them. I know it's more confusing than it has to be, I'm sorry.
**
** Don't judge me, norminette made me do it. xD
*/

typedef struct s_bstprintvars
{
	size_t			level;
	size_t			div;
	size_t			hpos;
	size_t			vpos;
}				t_bstprintvars;

typedef struct s_bstprint
{
	t_bsttermcaps	tcaps;
	struct winsize	wsize;
	t_bstprintvars	var;
}				t_bstprint;

size_t			ft_bintree_depth(t_bstnode *root);
//Style 1
t_bstnode		*ft_bintree_add(t_bstnode *root, long int data);
void			ft_bintree_balance(t_bstnode **root, t_bstnode *new_node);

//Style 2
//t_bstnode		*ft_bintree_add(t_bstnode *root, t_bstnode *new_node);
//t_bstnode		*create_new_node(long int data);

t_bstnode		*ft_bintree_search(t_bstnode *root, long int data);
t_bstnode		*ft_bintree_free(t_bstnode *root);
int				ft_bintree_print(t_bstnode *root, size_t depth_limit);
int				ft_bintree_termcaps_init(t_bsttermcaps *tcaps);

#endif
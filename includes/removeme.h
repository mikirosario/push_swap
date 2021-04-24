/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removeme.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 03:14:24 by miki              #+#    #+#             */
/*   Updated: 2021/04/15 13:47:43 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <termcap.h>
#include <curses.h>
#include <term.h>

typedef struct s_termcaps
{
	char	termbuf[2048];
	char	capbuf[2048];
	char	*cur_mov;
	char	*scroll_up;
}				t_termcaps;

/*
** This is just to get a rough graphical printout of some trees for development
** purposes, full of illegal funcions, remove from final version.
*/

void put_btree(t_bstnode *root);
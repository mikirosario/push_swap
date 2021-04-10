/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_window_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:30:25 by miki              #+#    #+#             */
/*   Updated: 2021/04/08 23:44:24 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

/*
** Thus function will save the column width and row height of the window in the
** winsize struct. It returns 0 if unsuccessful and 1 if successful.
**
** Careful! Only use it in projects where ioctl is allowed. :)
*/

int	ft_get_window_size(struct winsize *wsize)
{
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, wsize) == -1 \
	 || (wsize->ws_col == 0 || wsize->ws_row == 0))
		return (0);
	return (1);
}

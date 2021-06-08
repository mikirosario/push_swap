/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 20:55:11 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/08 21:16:20 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** This function chooses a color based on the percentage of completion of the
** progress bar. Self-explanatory. :)
*/

static void	color_bar(int pct)
{
	if (pct < 25)
		write(STDERR_FILENO, RED, ft_strlen(RED));
	else if (pct < 50)
		write(STDERR_FILENO, YEL, ft_strlen(YEL));
	else if (pct < 75)
		write(STDERR_FILENO, CYN, ft_strlen(CYN));
	else
		write(STDERR_FILENO, GRN, ft_strlen(GRN));
}

/*
** This function displays a little progress bar on STDERR while the program is
** processing instructions, so the user doesn't get bored.
**
** The function is called whenever the program finishes ordering a stack for a
** given range size. The progress counter counts how many stacks have been
** ordered. We want to avoid making the bar too long, so well adjust this to
** show a single character for every 4 stacks ordered. We control this with the
** adjusted counter, which ticks up once for every four ticks of the progress
** counter (that is, when progress % 4 == 0).
**
** Next we set the pct variable to hold the percentage of completion. The total
** length of the bar is set in pswap->pbar.len to be equal to 100 - the starting
** test range size. For example, if we start with a test range of 1, given that
** for every new iteration we increment the test range by 1, we get 99
** iterations. If we start with a test range of 20, we get 80 iterations (from
** 20 to 100). So that is the total length of our progress bar. But remember, we
** want to downsize it so it is not so big. Since we're only displaying one
** new character for every 4 iterations, we also want to reduce the size of the
** progress bar by 25%. So, we take the pbar.len divided by 4 as our real total
** length. Then we just apply the simple formula to calculate what percentage
** adjusted is of the total pbar.len (pct = adjusted/(total * 100)). The numbers
** do need to be cast to doubles for the calculation, and then the result recast
** to an int.
**
** That will give us the percentage of completion in the pct variable. We run
** that through itoa so we can print it to screen. We also pass it to the
** color_bar function to decide what color to paint the bar.
**
** From there, the first write passes the ANSI commands for moving up one line
** and clearing the line. Then we print the full part of the bar with the '#'
** symbol. I have a bar with the appropriate number of '#' for a full bar at
** pbar.bar, so we just write adjusted bytes of it. :) Then we do the same for
** the empty part of the bar. I have a bar with the appropriate number of '-'
** for an empty bar at pbar.empty, so we just write pbar.len / 4 - adjusted of
** that. Then we write a space. Then we write the percentage. Then we write the
** '%' symbol. Then we write a newline. Finally, we reset the color and free the
** memory occupied by the itoa string.
*/

void	display_progress_bar(t_pswap *pswap)
{
	static size_t	progress = 0;
	static size_t	adjusted = 0;
	int				pct;
	char			*alnum_pct;

	progress++;
	if (!(progress % 4))
		adjusted++;
	if (!adjusted)
		pct = 0;
	else
		pct = (int)((double)adjusted / (pswap->pbar.len / 4) * 100);
	alnum_pct = ft_itoa(pct);
	color_bar(pct);
	write(STDERR_FILENO, "\e[1A\e[2K", 8);
	write(STDERR_FILENO, pswap->pbar.bar, adjusted);
	write(STDERR_FILENO, pswap->pbar.empty, (pswap->pbar.len / 4) - adjusted);
	write(STDERR_FILENO, " ", 1);
	write(STDERR_FILENO, alnum_pct, ft_strlen(alnum_pct));
	write(STDERR_FILENO, "%", 1);
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, RESET, ft_strlen(RESET));
	alnum_pct = ft_del(alnum_pct);
}

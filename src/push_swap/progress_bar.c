/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 20:55:11 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/04 22:15:29 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	if (pct < 25)
		write(STDERR_FILENO, RED, ft_strlen(RED));
	else if (pct < 50)
		write(STDERR_FILENO, YEL, ft_strlen(YEL));
	else if (pct < 75)
		write(STDERR_FILENO, CYN, ft_strlen(CYN));
	else
		write(STDERR_FILENO, GRN, ft_strlen(GRN));
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

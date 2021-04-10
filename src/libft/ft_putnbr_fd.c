/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:36:08 by mrosario          #+#    #+#             */
/*   Updated: 2021/04/07 00:51:40 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(long long int n, int fd)
{
	long long int	ncpy;

	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	ncpy = (long long int)n;
	if (n < 0)
	{
		ncpy = -ncpy;
		ft_putchar_fd('-', fd);
	}
	if (ncpy < 10)
		ft_putchar_fd(ncpy + 48, fd);
	else
	{
		ft_putnbr_fd(ncpy / 10, fd);
		ft_putchar_fd((ncpy % 10) + 48, fd);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 20:59:53 by mrosario          #+#    #+#             */
/*   Updated: 2021/04/07 07:26:29 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int	ft_putchar(int chr)
{
	if (write(STDOUT_FILENO, &chr, 1) == -1)
		return (EOF);
	return (chr);
}

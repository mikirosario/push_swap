/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:07:56 by miki              #+#    #+#             */
/*   Updated: 2021/04/23 19:27:36 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_bintree.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_checker
{
	t_bstnode	*bintree;
	int			*stack_a;
}				t_checker;

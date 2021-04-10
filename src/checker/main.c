/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:42:53 by miki              #+#    #+#             */
/*   Updated: 2021/04/10 21:55:28 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_bintree.h"
#include "limits.h"
#include <unistd.h>
#include <stdio.h>
//#include "ansi_color_codes.h"

//#include "removeme.h"


void	print_error(char *error_msg, char *ansi_color_code)
{
	write(STDERR_FILENO, ansi_color_code, ft_strlen(ansi_color_code));
	ft_putendl_fd(error_msg, STDERR_FILENO);
	write(STDERR_FILENO, RESET, 4);
}

int	exit_failure(char *error_msg)
{
	//freeme
	print_error(error_msg, RED);
	exit(EXIT_FAILURE);
}

/*
**
** OK, so we get an unspecified number of arguments, each with numbers to be
** checked for adequacy and then put in stack a.
**
** OK, first I'll use numbuf to store each individual number in the arguments
** and convert them into integers. I have a handy libft function to find the
** numbers called ft_getnextnum.
*/

int	main(int argc, char **argv)
{
	size_t		i;
	char		numbuf[11];
	char		*num;

	if (argc < 2 || argv[1][0] == '\0')
		exit_failure("Fatal error: No argument provided");
	num = argv[1];
	while (*num)
	{
		ft_bzero(numbuf, 11);
		//If the number is not a digit and is not a space, non-number failure
		if (ft_isspace(*num))
			num = ft_getnextnum(num);
		if (!ft_isdigit(*num))
			exit_failure("Argument contains non-numbers");
		i = 0;
		while (ft_isdigit(num[i]))
			i++;
		while (ft_isdigit(*num))
			numbuf[10 - --i] = *num++;
	}
	printf("TEST: %d", ft_atoi(numbuf));
	return (0);
}
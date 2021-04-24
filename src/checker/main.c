/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:42:53 by miki              #+#    #+#             */
/*   Updated: 2021/04/24 21:48:21 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
//#include "ansi_color_codes.h"

//#include "removeme.h"


void	print_error(char *error_msg, char *ansi_color_code)
{
	write(STDERR_FILENO, ansi_color_code, ft_strlen(ansi_color_code));
ft_putendl_fd(error_msg, STDERR_FILENO);
	write(STDERR_FILENO, RESET, 4);
}

int	exit_failure(char *error_msg, t_checker *checker)
{
	//freeme
	if (checker->bintree)
		checker->bintree = ft_bintree_free(checker->bintree);
	if (error_msg)
		print_error(error_msg, RED);
	exit(EXIT_FAILURE);
}

/*
** For numbers of 10 digits, we check to make sure they don't exceed INT_MAX or
** INT_MIN (if negative), which I hardcode here since I'm already assuming it
** will be 10 digits long and all, so I'm assuming 4 byte integers. :p Otherwise
** any number less than 10 digits long will always be below the maximum and any
** number more than 10 digits long will always be above it.
**
** Yeah I know if I really wanted to make my push_swap portable I should check
** how many bytes are in an integer in the local implementation and all. :p
*/

int	exceeded_max_int(char *num, char neg)
{
	char	*intmax;
	int		result;

	if (neg == '-')
		intmax = "2147483648";
	else
		intmax = "2147483647";
	result = ft_strncmp(num, intmax, 10);
	if (result > 0)
		return (1);
	return (0);
}

/*
**
** OK, so we get an unspecified number of arguments, each with numbers to be
** checked for adequacy and then put in stack a.
**
** OK, first I'll use numbuf to store each individual number in the arguments
** and convert them into integers. The numbuf has room for 11 bytes plus the
** nul byte to make space for the minus sign if needed.
*/

int	main(int argc, char **argv)
{
	size_t		i;
	//size_t		x;
	char		**args;
	char		numbuf[12];
	char		*num;
	//t_bstnode	*bintree = NULL;
	size_t		stack_size;
	t_checker	checker;

	ft_bzero(&checker, sizeof(t_checker));
	//No argument provided :p
	if (argc < 2 || argv[1][0] == '\0')
		exit_failure(NULL, &checker);
	numbuf[11] = 0;
	//x = 1;
	args = &argv[1];
	stack_size = 0;
	while (*args)
	{
		num = *args++;
		while (*num)
		{
			ft_memset(numbuf, '0', 11);
			num = ft_skipspaces(num);
			if (*num == '-')
				numbuf[0] = *num++;
			i = 0;
			while (ft_isdigit(num[i]))
				i++;
			if (!ft_isspace(num[i]) && num[i])
				exit_failure("Argument is not an integer", &checker);
			else if (i > 10 || (i == 10 && exceeded_max_int(num, numbuf[0])))
				exit_failure("Number too large", &checker);
			while (&num[i] > num)
				numbuf[11 - i--] = *num++;
			printf("TEST: %d\n", ft_atoi(numbuf));
			if (ft_bintree_search(checker.bintree, ft_atoi(numbuf)))
				exit_failure("Duplicate number", &checker);
			checker.bintree = ft_bintree_add(checker.bintree, ft_atoi(numbuf));
			stack_size += 4;
			checker.stack_a = ft_realloc(checker.stack_a, stack_size, stack_size - 4);
			//size to pos ya sé que es feo :p
			checker.stack_a[(stack_size - 4) / 4] = ft_atoi(numbuf);
		}
	}
	//DEBUG CODE
	ft_bintree_print(checker.bintree, 0);
	printf("Stack A:\n");
	for (size_t i = 0; i < stack_size; i += 4)
	{
		printf("%d\n", checker.stack_a[i/4]);
	}
	//DEBUG CODE

	//WAIT FOR STDIN COMMANDS
	ssize_t	size;
	char	buf[3];

	ft_bzero(buf, 3);
	//ft_memset(buf, '0', 3);
	size = read(STDIN_FILENO, buf, 3);

	printf("%s\n", buf);
	//
	checker.stack_a = ft_del(checker.stack_a);
	checker.bintree = ft_bintree_free(checker.bintree);
	return (0);
}
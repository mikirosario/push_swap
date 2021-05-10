/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_stacks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 20:36:10 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/10 17:40:47 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	debug_func(t_checker *checker)
{
	//DEBUG CODE
	ft_bintree_print(checker->bintree, 0);
	printf("UNSORTED STACK A:\n");
	for (t_list *tmp = checker->stack_a; tmp; tmp = tmp->next)
	{
		if (tmp->content)
			printf("%d\n", *(int *)tmp->content);
	}
	for (t_list *tmp = checker->stack_b; tmp; tmp = tmp->next)
	{
		if (tmp->content)
			printf("%d\n", *(int *)tmp->content);
	}
	// for (size_t j = 0; j < stack_size; j += 8)
	// {
	// 	*checker->stack_b[j/8] = *checker->stack_a[j/8];
	// }
	// printf("Stack B:\n");
	// for (size_t i = 0; i < stack_size; i += 8)
	// {
	// 	printf("%d\n", *checker->stack_b[i/8]);
	// }
	//DEBUG CODE
}

/*
** This function generates an empty stack_b, with space for the same number of
** integers as stack_a, but every integer pointer is initially NULL, signifying
** no element is present.
*/

int	generate_stack_b(t_checker *checker)
{
	//checker->stack_b = (int**)ft_calloc(checker->stack_size, 1);
	checker->stack_b = NULL;
	// //DEBUG CODE
	// size_t i = 0;
	// while (i < checker->stack_size)
	// {
	// 	checker->stack_b[i] = (int*)ft_calloc(1, sizeof(int));
	// 	i++;
	// }
	// //DEBUG CODE
	return (1);
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

int	exceeded_max_int(char *num, char sign)
{
	char	*intmax;
	int		result;

	if (sign == '-')
		intmax = "2147483648";
	else
		intmax = "2147483647";
	result = ft_strncmp(num, intmax, 10);
	if (result > 0)
		return (1);
	return (0);
}

/*
** This function identifies the next token in the string (the sub-string after
** any spaces are skipped and until the next space or NUL char). If that token
** is a valid number, the size of the number is saved to *numlen and the start
** address of the number is returned. The number's sign is also copied to the
** first byte of the number buffer numbuf.
**
** A valid number may start with a single '-' or '+' and contain up to 10
** digits, may not be larger than INT_MAX or smaller than INT_MIN, and zeros on
** the left are skipped.
**
** If the number is invalid the program terminates and throws an error.
** (Probably will eventually do the termination elsewhere and return NULL).
**
** The program will throw an error and terminate if:
**
** 1. An argument does not contain an integer.
** 2. An integer is too large (greater than INT_MAX or less than INT_MIN).
*/

static char	*next_num(t_checker *checker, char *numstart, char *numbuf, size_t *numlen)
{
	numstart = ft_skipspaces(numstart);
	//Number may start with a single '-' or '+'. A space for the sign is reserved in the first byte of numbuf.
	//If there is no sign, the first byte in numbuf defaults to '0' (in ASCII).
	//If there is a sign, the number is assumed to begin after the sign.
	if (*numstart == '-' || *numstart == '+')
		numbuf[0] = *numstart++;
	if (!ft_isdigit(*numstart)) //Argument is not an integer if number starts with char that is not a digit.
		exit_failure("Error", checker);
	*numlen = 0;
	//Salta ceros a la izquierda mientras *num == 0 y el carácter siguiente sea cualquier dígito
	while (*numstart == '0' && ft_isdigit(*(numstart + 1)))
		numstart++;
	while (ft_isdigit(numstart[*numlen]))
		(*numlen)++;
	//Argument is not an integer if after all the digits we find char that is neither space nor nul
	if (!ft_isspace(numstart[*numlen]) && numstart[*numlen])
		exit_failure("Error", checker);
	//Number too large
	else if (*numlen > 10 || (*numlen == 10 && exceeded_max_int(numstart, numbuf[0])))
		exit_failure("Error", checker);
	return (numstart);
}


/*
** This function will search for the next number in the argument string 'num',
** convert that number into an integer and pass it into the buffer numbuf along
** with its sign, if any. The numbuf will then be used to generate an integer,
** which will be checked against a binary tree of preceding integers to check
** for duplicates, and then added to the tree if there are no duplicates.
**
** Then stack_a, which is a stack of integer pointers, will be reallocated to
** make way for the new pointer, memory will be reserved for an integer, and
** the last pointer in stack_a will be made to point to the newly created
** integer. Then this new integer is set to the number in numbuf.
**
** The program will throw an error and terminate if:
**
** 1. An integer is repeated.
*/

char	*generate_stack_a(t_checker *checker, char *num)
{
	t_list		*new;
	char		numbuf[12];
	size_t		numlen;
	
	numbuf[11] = 0;
	ft_memset(numbuf, '0', 11);
	num = next_num(checker, num, numbuf, &numlen);
	while (&num[numlen] > num)
		numbuf[11 - numlen--] = *num++;
	// //DEBUG
	// printf("TEST: %d\n", ft_atoi(numbuf));
	// //DEBUG
	//Duplicate number
	if (ft_bintree_search(checker->bintree, ft_atoi(numbuf)))
		exit_failure("Error", checker);
	checker->bintree = ft_bintree_add(checker->bintree, ft_atoi(numbuf));
	new = ft_lstnew(ft_calloc(1, sizeof(int)));
	*(int *)new->content = ft_atoi(numbuf);
	if (!checker->stack_a)
		checker->stack_a = new;
	else
		ft_lstadd_back(&checker->stack_a, new);
	//checker->stack_size += sizeof(int*);
	//checker->stack_a = ft_realloc(checker->stack_a, checker->stack_size, checker->stack_size - sizeof(int*));
	// //size to pos ya sé que es feo :p
	//checker->stack_a[(checker->stack_size - sizeof(int*)) / sizeof(int*)] = ft_calloc(1, sizeof(int));
	// *checker->stack_a[(checker->stack_size - sizeof(int*)) / sizeof(int*)] = ft_atoi(numbuf);
	return (num);
}

/*
** In case of an error the progam will print Error to stderr and terminate.
**
** A red-black binary tree is created out of the integers to check for
** duplicates. This is just a voluntary exercise on my part to practise writing
** and using binary tree functions. :)
**
** The function returns 1 if successful, because it will probably be further
** split and rewritten to return 0 if unsuccessful for a single exit_failure
** call instruction...
*/

int	generate_stacks(char **argv, t_checker *checker)
{
	//size_t		numlen;
	char		**args;
	//char		numbuf[12];
	char		*num;
	//size_t		stack_size;

	//numbuf[11] = 0;
	args = &argv[1];
	while (*args)
	{
		num = *args++;
		while (*num)
			num = generate_stack_a(checker, num);
	}
	generate_stack_b(checker);
	//DEBUG CODE
	debug_func(checker);
	//DEBUG CODE

	return (1);
}
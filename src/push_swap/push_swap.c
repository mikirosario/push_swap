/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 21:55:20 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/23 23:42:01 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	freeme(t_pswap *pswap)
{
	if (pswap->stack_a)
		ft_lstclear(&pswap->stack_a, free);
	if (pswap->stack_b)
		ft_lstclear(&pswap->stack_b, free);
	if (pswap->mask_a.vector)
		pswap->mask_a.vector = ft_del(pswap->mask_a.vector);
	if (!pswap->mask_b.vector)
		pswap->mask_b.vector = ft_del(pswap->mask_b.vector);
	pswap->bintree = ft_bintree_free(pswap->bintree);
	if (pswap->bintree)
		pswap->bintree = ft_bintree_free(pswap->bintree);
	if (pswap->lst)
		ft_lstclear(&pswap->lst, free);
}

void	print_error(char *error_msg, char *ansi_color_code)
{
	write(STDERR_FILENO, ansi_color_code, ft_strlen(ansi_color_code));
	ft_putendl_fd(error_msg, STDERR_FILENO);
	write(STDERR_FILENO, RESET, 4);
}

void	exit_failure(char *error_msg, t_pswap *pswap)
{
	if (error_msg)
		print_error(error_msg, RED);
	freeme(pswap);
	exit(EXIT_FAILURE);
}

void	exit_success(t_pswap *pswap)
{
	freeme(pswap);
	exit(EXIT_SUCCESS);
}


static void	debug_func(t_pswap *pswap)
{
	//DEBUG CODE
	// ft_bintree_print(pswap->bintree, 0);
	printf("UNSORTED STACK A:\n");
	for (t_list *tmp = pswap->stack_a; tmp; tmp = tmp->next)
	{
		if (tmp->content)
			printf("%d\n", *(int *)tmp->content);
	}
	for (t_list *tmp = pswap->stack_b; tmp; tmp = tmp->next)
	{
		if (tmp->content)
			printf("%d\n", *(int *)tmp->content);
	}
	//DEBUG CODE
}

/*
** This function generates an empty stack_b, with space for the same number of
** integers as stack_a, but every integer pointer is initially NULL, signifying
** no element is present.
*/

static void	generate_stack_b(t_pswap *pswap)
{
	pswap->stack_b = NULL;
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

static int	exceeded_max_int(char *num, char sign)
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

static char	*next_num(t_pswap *pswap, char *numstart, char *numbuf, \
size_t *numlen)
{
	numstart = ft_skipspaces(numstart);
	if (*numstart == '-' || *numstart == '+')
		numbuf[0] = *numstart++;
	if (!ft_isdigit(*numstart))
		exit_failure("Error", pswap);
	*numlen = 0;
	while (*numstart == '0' && ft_isdigit(*(numstart + 1)))
		numstart++;
	while (ft_isdigit(numstart[*numlen]))
		(*numlen)++;
	if (!ft_isspace(numstart[*numlen]) && numstart[*numlen])
		exit_failure("Error", pswap);
	else if (*numlen > 10 || (*numlen == 10 \
	 && exceeded_max_int(numstart, numbuf[0])))
		exit_failure("Error", pswap);
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

static char	*generate_stack_a(t_pswap *pswap, char *num)
{
	t_list		*new;
	char		numbuf[12];
	size_t		numlen;

	numbuf[11] = 0;
	ft_memset(numbuf, '0', 11);
	num = next_num(pswap, num, numbuf, &numlen);
	while (&num[numlen] > num)
		numbuf[11 - numlen--] = *num++;
	if (ft_bintree_search(pswap->bintree, ft_atoi(numbuf)))
		exit_failure("Error", pswap);
	pswap->bintree = ft_bintree_add(pswap->bintree, ft_atoi(numbuf));
	new = ft_lstnew(ft_calloc(1, sizeof(int)));
	*(int *)new->content = ft_atoi(numbuf);
	if (!pswap->stack_a)
		pswap->stack_a = new;
	else
		ft_lstadd_back(&pswap->stack_a, new);
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

int	generate_stacks(char **argv, t_pswap *pswap)
{
	char		**args;
	char		*num;

	args = &argv[1];
	while (*args)
	{
		num = *args++;
		while (*num)
			num = generate_stack_a(pswap, num);
	}
	generate_stack_b(pswap);

	//DEBUG CODE
	debug_func(pswap);
	//DEBUG CODE

	return (1);
}

void	count_numbers(t_pswap *pswap)
{
	t_list	*stack_a;

	stack_a = pswap->stack_a;
	//find out how many numbers there are
	while (stack_a)
	{
		stack_a = stack_a->next;
		pswap->numbers++;
	}
	//initialize stack_a_numbers to total numbers
	pswap->stack_a_numbers = pswap->numbers;
}

void	print_instructions(t_pswap *pswap)
{
	t_list	*instructions;

	instructions = pswap->lst;
	while (instructions)
	{
		ft_putendl_fd((char *)instructions->content, STDOUT_FILENO);
		instructions = instructions->next;
	}
	//debug code
	printf("Number of Movements: %zu\n", pswap->move_counter);
	printf("SORTED STACK A\n");
	for (t_list *lst = pswap->stack_a; lst; lst = lst->next)
		printf("%d\n", *(int *)lst->content);
	printf("SORTED STACK B\n");
	for (t_list *lst = pswap->stack_b; lst; lst = lst->next)
		printf("%d\n", *(int *)lst->content);
	//debug code
}

void	init(t_pswap *pswap)
{
	t_bstnode	*bintree;

	pswap->mask_a.vector = ft_calloc(pswap->numbers, sizeof(int));
	pswap->mask_b.vector = ft_calloc(pswap->numbers, sizeof(int));
	pswap->mask_a.start_index = 0;
	pswap->mask_a.end_index = pswap->numbers;
	pswap->mask_b.start_index = pswap->numbers;
	pswap->mask_b.end_index = pswap->numbers;

	bintree = pswap->bintree;
	while (bintree->left)
		bintree = bintree->left;
	pswap->num.smallest = (int)bintree->data;
	bintree = pswap->bintree;
	while(bintree->right)
		bintree = bintree->right;
	pswap->num.largest = (int)bintree->data;
}

void	get_relevant_numbers(t_pswap *pswap)
{
	t_list		*penult_a;
	t_list 		*penult_b;
	t_list		*a_extremes;

	penult_a = pswap->stack_a;
	penult_b = pswap->stack_b;
	a_extremes = pswap->stack_a;
	if (pswap->stack_a)
	{
		while (a_extremes)
		{
			if (pswap->num.a_smallest < *(int *)a_extremes->content)
				pswap->num.a_smallest = *(int *)a_extremes->content;
			if (pswap->num.a_largest > *(int *)a_extremes->content)
				pswap->num.a_largest = *(int *)a_extremes->content;
			a_extremes = a_extremes->next;
		}
		while (penult_a->next && penult_a->next->next)
			penult_a = penult_a->next;
		pswap->num.a_first = *(int *)pswap->stack_a->content;
		if (pswap->stack_a->next)
			pswap->num.a_second = *(int *)pswap->stack_a->next->content;
		else
			pswap->num.a_second = pswap->num.a_first;
		pswap->num.a_penult = *(int *)penult_a->content;
		pswap->num.a_last = *(int *)(ft_lstlast(pswap->stack_a))->content;
	}
	if (pswap->stack_b)
	{
		while (penult_b->next && penult_b->next->next)
			penult_b = penult_b->next;
		pswap->num.b_first = *(int *)pswap->stack_b->content;
		if (pswap->stack_b->next)
			pswap->num.b_second = *(int *)pswap->stack_b->next->content;
		else
			pswap->num.b_second = pswap->num.b_first;
		pswap->num.b_penult = *(int *)penult_b->content;
		pswap->num.b_last = *(int *)(ft_lstlast(pswap->stack_b))->content;
	}
}

int	main(int argc, char **argv)
{
	t_pswap	pswap;

	(void)argc;
	ft_bzero(&pswap, sizeof(t_pswap));
	generate_stacks(argv, &pswap);
	count_numbers(&pswap);
	// if (is_sorted(pswap))
	// 	return ;
	//find how many numbers there are
	init(&pswap);
	if (pswap.numbers > 1)
	{
		while (generate_instructions(&pswap))
		{
		}
		print_instructions(&pswap);
	}
	// if (are_contiguous(&pswap, 2, 0))
	// 	printf("CONTIGUOUS\n");
	// else
	// 	printf("NON-CONTIGUOUS\n");
	
	//debug code
	exit_success(&pswap);
}
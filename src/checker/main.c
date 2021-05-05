/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:42:53 by miki              #+#    #+#             */
/*   Updated: 2021/05/05 21:42:44 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
//#include "ansi_color_codes.h"

//#include "removeme.h"

void	freeme(t_checker *checker)
{
	checker->stack_a = ft_del(checker->stack_a);
	checker->bintree = ft_bintree_free(checker->bintree);
	if (checker->bintree)
		checker->bintree = ft_bintree_free(checker->bintree);
	if (checker->lst)
		ft_lstclear(&checker->lst, free);
}

void	print_error(char *error_msg, char *ansi_color_code)
{
	write(STDERR_FILENO, ansi_color_code, ft_strlen(ansi_color_code));
	ft_putendl_fd(error_msg, STDERR_FILENO);
	write(STDERR_FILENO, RESET, 4);
}

int	exit_failure(char *error_msg, t_checker *checker)
{
	if (error_msg)
		print_error(error_msg, RED);
	freeme(checker);
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
** Find an exact match for a null-terminated string 'match' in a string 'str'
** separated by a separator 'sep'. The separator 'sep' must be standard ASCII
** and may not be NUL and both string pointers must be valid.
**
** In case of an error, -1 is returned. In case of a match, 1 is returned. In
** case of no match, 0 is returned.
*/

int	ft_str_match(char *match, char *str, char sep)
{
	size_t	i;
	size_t	matchlen;
	size_t	toklen;

	if (sep == '\0' || !ft_isascii(sep) || str == NULL || match == NULL)
		return (-1);
	matchlen = ft_strlen(match);
	while (*str)
	{
		i = 0;
		if (*str == sep)
			while (*str == sep)
				str++;
		while (str[i] && str[i] != sep)
			i++;
		toklen = &str[i] - str;
		if (matchlen == toklen && !ft_strncmp(match, str, toklen))
			return (1);
		str = &str[i];
	}
	return (0);
}


/*
** This function will generate stack_a out of the integers passed to the program
** as arguments in order of receipt. Arguments with multiple integers separated
** spaces will be processed. Integers may be passed in one argument per integer
** or in several integers to an argument.
**
** The program will throw an error and terminate if:
**
** 1. An argument does not contain an integer.
** 2. An integer is too large (greater than INT_MAX or less than INT_MIN).
** 3. An integer is repeated.
**
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

int	generate_stack_a(char **argv, t_checker *checker)
{
	size_t		i;
	char		**args;
	char		numbuf[12];
	char		*num;
	size_t		stack_size;

	numbuf[11] = 0;
	args = &argv[1];
	stack_size = 0;
	while (*args)
	{
		num = *args++;
		while (*num)
		{
			ft_memset(numbuf, '0', 11);
			num = ft_skipspaces(num);
			if (*num == '-' || *num == '+')
				numbuf[0] = *num++;
			else if (!ft_isdigit(*num)) //Argument is not an integer if number starts with char that is not a digit, '-' or '+'.
				exit_failure("Error", checker);
			i = 0;
			//Elimina ceros a la izquierda
			while (*num == '0')
				num++;
			//Si después de los ceros no hay un dígito, vuelve uno al último cero
			if (!ft_isdigit(num[i]))
				num--;
			while (ft_isdigit(num[i]))
				i++;
			//Argument is not an integer if we find char that is neither space nor nul
			if (!ft_isspace(num[i]) && num[i])
				exit_failure("Error", checker);
			//Number too large
			else if (i > 10 || (i == 10 && exceeded_max_int(num, numbuf[0])))
				exit_failure("Error", checker);
			while (&num[i] > num)
				numbuf[11 - i--] = *num++;
			// //DEBUG
			// printf("TEST: %d\n", ft_atoi(numbuf));
			// //DEBUG
			//Duplicate number
			if (ft_bintree_search(checker->bintree, ft_atoi(numbuf)))
				exit_failure("Error", checker);
			checker->bintree = ft_bintree_add(checker->bintree, ft_atoi(numbuf));
			stack_size += 4;
			checker->stack_a = ft_realloc(checker->stack_a, stack_size, stack_size - 4);
			//size to pos ya sé que es feo :p
			checker->stack_a[(stack_size - 4) / 4] = ft_atoi(numbuf);
		}

	//DEBUG CODE
	ft_bintree_print(checker->bintree, 0);
	printf("Stack A:\n");
	for (size_t i = 0; i < stack_size; i += 4)
	{
		printf("%d\n", checker->stack_a[i/4]);
	}
	//DEBUG CODE
	}
	return (1);
}

/*
** OK, so we get an unspecified number of arguments, each with numbers to be
** checked for adequacy and then put in stack a.
**
** OK, first I'll use numbuf to store each individual number in the arguments
** and convert them into integers. The numbuf has room for 11 bytes plus the
** nul byte to make space for the minus sign if needed.
*/

int	main(int argc, char **argv)
{
	// size_t		i;
	// char		**args;
	// char		numbuf[12];
	// char		*num;
	// size_t		stack_size;
	t_checker	checker;

	ft_bzero(&checker, sizeof(t_checker));
	//No argument provided :p
	if (argc < 2 || argv[1][0] == '\0')
		exit_failure(NULL, &checker);
	generate_stack_a(argv, &checker);
	// numbuf[11] = 0;
	// //x = 1;
	// args = &argv[1];
	// stack_size = 0;
	// while (*args)
	// {
	// 	num = *args++;
	// 	while (*num)
	// 	{
	// 		ft_memset(numbuf, '0', 11);
	// 		num = ft_skipspaces(num);
	// 		if (*num == '-')
	// 			numbuf[0] = *num++;
	// 		i = 0;
	// 		while (ft_isdigit(num[i]))
	// 			i++;
	// 		//Argument is not an integer
	// 		if (!ft_isspace(num[i]) && num[i])
	// 			exit_failure("Error", &checker);
	// 		//Number too large
	// 		else if (i > 10 || (i == 10 && exceeded_max_int(num, numbuf[0])))
	// 			exit_failure("Error", &checker);
	// 		while (&num[i] > num)
	// 			numbuf[11 - i--] = *num++;
	// 		//DEBUG
	// 		printf("TEST: %d\n", ft_atoi(numbuf));
	// 		//DEBUG
	// 		//Duplicate number
	// 		if (ft_bintree_search(checker.bintree, ft_atoi(numbuf)))
	// 			exit_failure("Error", &checker);
	// 		checker.bintree = ft_bintree_add(checker.bintree, ft_atoi(numbuf));
	// 		stack_size += 4;
	// 		checker.stack_a = ft_realloc(checker.stack_a, stack_size, stack_size - 4);
	// 		//size to pos ya sé que es feo :p
	// 		checker.stack_a[(stack_size - 4) / 4] = ft_atoi(numbuf);
	// 	}
	// }

//printf("DONE\n");
	//WAIT FOR STDIN COMMANDS
	ssize_t	size;
	//char	buf[4];
	char	*buf;
	char	*content;
	t_list	*new;

	//ft_memset(buf, '0', 3);

	while(ft_get_next_line(STDIN_FILENO, &buf) > 0)
	{
		if (ft_str_match(buf, INSTRUCTIONS, ':') < 1)
			exit_failure("Error", &checker);
		content = ft_strdup(buf);
		new = ft_lstnew(content);
		//printf("%s\n", new->content);
		if(checker.lst)
			ft_lstadd_back(&checker.lst, new);
		else
			checker.lst = new;
		//printf("%s\n", checker.lst->content);
		//if (checker.lst->next)
		//	printf("%s\n", checker.lst->next->content);
		buf = ft_del(buf);
		size = read(STDIN_FILENO, buf, 4);
	}

	//debug code//
	t_list *tmp = checker.lst;
	while(tmp)
	{
		//printf("%s\n", tmp->content);
		if (ft_str_match(tmp->content, INSTRUCTIONS, ':') == 0)
			printf("BAD BUNNY, %s no existe\n", tmp->content);
		else if (ft_str_match(tmp->content, INSTRUCTIONS, ':') == 1)
			printf("GOOD BUNNY, %s existe\n", tmp->content);
		else
			printf("WTF BUNNY?\n");
		tmp = tmp->next;
	}
	//debug code

	return (0);
}
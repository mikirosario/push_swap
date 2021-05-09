/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:42:53 by miki              #+#    #+#             */
/*   Updated: 2021/05/09 21:55:51 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
//#include "ansi_color_codes.h"

//#include "removeme.h"

void	freeme(t_checker *checker)
{
	size_t	i;

	if (checker->stack_a)
	{
		i = 0;
		while (i < checker->stack_size / sizeof(int *))
		{
			if (checker->stack_a[i])
				checker->stack_a[i] = ft_del(checker->stack_a[i]);
			i++;
		}
		checker->stack_a = ft_del(checker->stack_a);
	}
	if (checker->stack_b)
	{
		i = 0;
		while (i < checker->stack_size / sizeof(int *))
		{
			if (checker->stack_b[i])
				checker->stack_b[i] = ft_del(checker->stack_b[i]);
			i++;
		}
		checker->stack_b = ft_del(checker->stack_b);
	}
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

int	sort_stack(t_checker *checker, char *instruction)
{
	size_t	i;
	int		tmp;

	if (!ft_strcmp(instruction, "sa"))
		sa_move(checker);
	else if (!ft_strcmp(instruction, "sb"))
		{
			if (!checker->stack_b[0] || !checker->stack_b[1])
				return (0);
			tmp = *checker->stack_b[1];
			*checker->stack_b[1] = *checker->stack_b[0];
			*checker->stack_b[0] = tmp;
		}
	
	printf("SORTED STACK A:\n");
	i =  0;
	while (i < (checker->stack_size / 8))
	{
		if (checker->stack_a[i])
			printf("%d\n", *checker->stack_a[i]);
		i++;
	}
	printf("\nSORTED STACK B:\n");
	i = 0;
	while (i < (checker->stack_size / 8))
	{
		if (checker->stack_b[i])
			printf("%d\n", *checker->stack_b[i]);
		i++;
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
	generate_stacks(argv, &checker);

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

	t_list	*instruction;
	instruction = checker.lst;
	while (instruction)
	{
		sort_stack(&checker, instruction->content);
		instruction = instruction->next;
	}
	// //debug code//
	// t_list *tmp = checker.lst;
	// while(tmp)
	// {
	// 	//printf("%s\n", tmp->content);
	// 	if (ft_str_match(tmp->content, INSTRUCTIONS, ':') == 0)
	// 		printf("BAD BUNNY, %s no existe\n", tmp->content);
	// 	else if (ft_str_match(tmp->content, INSTRUCTIONS, ':') == 1)
	// 		printf("GOOD BUNNY, %s existe\n", tmp->content);
	// 	else
	// 		printf("WTF BUNNY?\n");
	// 	tmp = tmp->next;
	// }
	// //debug code


	return (0);
}
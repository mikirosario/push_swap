/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:42:53 by miki              #+#    #+#             */
/*   Updated: 2021/05/10 20:34:06 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
//#include "ansi_color_codes.h"

//#include "removeme.h"


static t_list	*find_preceding_member(t_list *lst, t_list *member)
{
	if (lst == member)
		return (NULL);
	while (lst->next != member)
		lst = lst->next;
	return (lst);
}

void	ft_lst_removeone(t_list **alst, t_list *remove)
{
	t_list	*subsequent_member;
	t_list	*preceding_member;

	subsequent_member = remove->next;
	preceding_member = find_preceding_member(*alst, remove);
	if (preceding_member == NULL)
	{
		ft_lstdelone(remove, free);
		*alst = subsequent_member;
	}
	else
	{
		ft_lstdelone(remove, free);
		preceding_member->next = subsequent_member;
	}
}

void	freeme(t_checker *checker)
{
	if (checker->stack_a)
		ft_lstclear(&checker->stack_a, free);
	// if (checker->stack_a)
	// {
	// 	i = 0;
	// 	while (i < checker->stack_size / sizeof(int *))
	// 	{
	// 		if (checker->stack_a[i])
	// 			checker->stack_a[i] = ft_del(checker->stack_a[i]);
	// 		i++;
	// 	}
	// 	checker->stack_a = ft_del(checker->stack_a);
	// }
	// if (checker->stack_b)
	// {
	// 	i = 0;
	// 	while (i < checker->stack_size / sizeof(int *))
	// 	{
	// 		if (checker->stack_b[i])
	// 			checker->stack_b[i] = ft_del(checker->stack_b[i]);
	// 		i++;
	// 	}
	// 	checker->stack_b = ft_del(checker->stack_b);
	// }
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
	if (!ft_strcmp(instruction, "sa"))
		sa_move(checker);
	else if (!ft_strcmp(instruction, "sb"))
		sb_move(checker);
	else if (!ft_strcmp(instruction, "ss"))
		ss_move(checker);
	else if (!ft_strcmp(instruction, "pa"))
	 	pa_move(checker);
	else if (!ft_strcmp(instruction, "pb"))
	 	pb_move(checker);
	else if (!ft_strcmp(instruction, "ra"))
		ra_move(checker);
	else if (!ft_strcmp(instruction, "rb"))
		rb_move(checker);
	else if (!ft_strcmp(instruction, "rr"))
		rr_move(checker);
	
	printf("SORTED STACK A:\n");
	for (t_list *tmp = checker->stack_a; tmp; tmp = tmp->next)
	{
		if (tmp->content)
			printf("%d\n", *(int *)tmp->content);
	}
	printf("\nSORTED STACK B:\n");
	for (t_list *tmp = checker->stack_b; tmp; tmp = tmp->next)
	{
		if (tmp->content)
			printf("%d\n", *(int *)tmp->content);
	}
	printf("\n");
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
	int		ret;
	//char	buf[4];
	char	*buf;
	char	*content;
	t_list	*new;

	//ft_memset(buf, '0', 3);
	ret = 1;
	while(ret > 0)
	{
		ret = ft_get_next_line(STDIN_FILENO, &buf);
		if (ret == -1)
			exit_failure("GNL Error", &checker);
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
		//size = read(STDIN_FILENO, buf, 4);
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
	// 	printf("%s\n", (char *)tmp->content);
	// 	if (ft_str_match(tmp->content, INSTRUCTIONS, ':') == 0)
	// 		printf("BAD BUNNY, %s no existe\n", (char *)tmp->content);
	// 	else if (ft_str_match(tmp->content, INSTRUCTIONS, ':') == 1)
	// 		printf("GOOD BUNNY, %s existe\n", (char *)tmp->content);
	// 	else
	// 		printf("WTF BUNNY?\n");
	// 	tmp = tmp->next;
	// }
	// //debug code


	return (0);
}
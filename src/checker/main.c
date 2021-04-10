/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 20:42:53 by miki              #+#    #+#             */
/*   Updated: 2021/04/10 09:33:40 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_bintree.h"
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


int	main(int argc, char **argv)
{
	if (argc < 2 || argv[1][0] == '\0')
		exit_failure("Fatal error: No argument provided");
	else if (argc > 2)
		exit_failure("Fatal error: Too many arguments");
	
	//BINTREE TEST
	t_bstnode *root = NULL;

	// root = ft_bintree_add(NULL, 200);
	// ft_bintree_add(root, 300);
	// ft_bintree_add(root, 220);
	// ft_bintree_add(root, 140);
	// ft_bintree_add(root, 567);
	// ft_bintree_add(root, 890);
	// ft_bintree_add(root, 24);
	// ft_bintree_add(root, 42);
	
	//Style 2
	//t_bstnode *new_node;

	int arr[19] = {200, 300, 220, 140, 567, 890, 24, 42, 9, 0, 192, 384, 283, 475, 49, 273, 44, 485, 987};
	for (int i = 0; i < 19; i++)
	{
		//Style 2
		// new_node = create_new_node(arr[i]);
		// root = ft_bintree_add(root, new_node);
		//Style 1
		root = ft_bintree_add(root, arr[i]);
	}



	if (ft_bintree_search(root, 42))
		printf("42 Exists\n");
	//ft_bintree_print(root, 4);
	t_bstnode *tmp1 = ft_bintree_search(root, 140);
	printf("DOES 140 REALLY HAVE RIGHT CHILD?: %s\n", tmp1->right ? "YES" : "NO");
	t_bstnode *tmp2 = ft_bintree_search(root, 567);
	printf("DOES 567 REALLY HAVE LEFT CHILD?: %s\n", tmp2->left ? "YES" : "NO");
	printf("DO 140 and 567 REALLY HAVE THE SAME CHILD?: %s\n", tmp1->right == tmp2->left ? "YES" : "NO");
	printf("WHO IS 140's RIGHT CHILD? %d\n", (int)tmp1->right->data);
	printf("WHO IS 567's LEFT CHILD? %d\n", (int)tmp2->left->data);
	root = ft_bintree_free(root);
	//printf("Sizeof T_bstnode: %zu\n", sizeof(long long int *));
	return (0);
}
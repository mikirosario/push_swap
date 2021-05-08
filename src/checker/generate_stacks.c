/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_stacks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 20:36:10 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/08 21:16:27 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include checker.h

int	generate_stacks(char **argv, t_checker *checker)
{
	size_t		numlen;
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
			stack_size += 4;
			checker->stack_a = ft_realloc(checker->stack_a, stack_size, stack_size - 4);
			//size to pos ya sé que es feo :p
			checker->stack_a[(stack_size - 4) / 4] = ft_atoi(numbuf);
		}
	checker->stack_b = ft_calloc(stack_size / 4, sizeof(int));
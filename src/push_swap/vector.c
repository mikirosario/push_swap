/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 15:34:23 by miki              #+#    #+#             */
/*   Updated: 2021/05/17 16:34:19 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "errno.h"

/*
** This function reserves memory for an vector of integers. If an vector already
** exists, it will reallocate it and
** increment its size by ARRAY_BUF * sizeof(void *) bytes.
**
** An vector has a buffer of 1024 bytes for as many as 128 pointers to any vector
** value. Values can be added with the add method. If more space is needed to
** add new values, the vector will be reallocated adding 1024 more bytes for 128
** more pointers. The function isn't protected against misuse or anything fancy,
** but it loosely imitates C++. Did this for convenience as I got tired of
** juggling vector memory. ;p
**
** If allocation fails or it's passed a NULL pointer, 0 will be returned. If
** successful, 1 will be returned.
*/

int	vector_realloc(t_vector *vector)
{
	int		*old_vector;
	int		*new_vector;
	size_t	old_allocated_mem;
	size_t	new_allocated_mem;
	size_t	index;

	if (vector == NULL)
		return (0);
	old_allocated_mem = vector->allocated_mem;
	new_allocated_mem = vector->allocated_mem + ARRAY_BUF;
	old_vector = vector->start;
	index = 0;
	if (vector->index)
		while (&vector->start[index] != vector->index)
			index++;
	new_vector = ft_realloc(old_vector, new_allocated_mem * sizeof(int), old_allocated_mem * sizeof(int));
	if (new_vector)
	{
		vector->start = new_vector;
		vector->index = &new_vector[index];
		if (vector->len)
			vector->end = &new_vector[vector->len - 1];
		vector->allocated_mem = new_allocated_mem;
	}
	else
		return (0);
	return (1);
}

/*
** This function removes the integer pointed to by the pointer passed as remove
** from the vector in the vector object passed as vector. If a NULL pointer is
** passed or a vector object without an assigned vector is passed, 0 is
** returned. If the address passed as remove cannot be found in the vector, 0 is
** returned. Otherwise, the integer pointed to by remove is set to 0, all
** integers right of it are shifted left until vector->end, the vector->end
** pointer is decremented by one, and the vector->len counter is also
** decremented by one.
**
** All memory assigned to the vector that is not occupied by a declared integer
** is kept at 0.
*/

int	vector_rem(t_vector *vector, int *remove)
{
	int	*index;

	if (!vector || !vector->start)
		return (0);
	index = vector->start;
	while (index != vector->end)
	{
		if (index == remove)
			break;
		index++;
	}
	if (index != remove)
		return (0);
	*index = 0;
	while (index != vector->end)
	{
		*index = *(index + 1);
		index++;
	}
	*vector->end-- = 0;
	vector->len--;
	return (1);
}

/*
** This function adds the integer passed as add to the vector in the vector
** object passed as vector. If a NULL pointer is passed to vector_add or if
** memory expansion is needed to fit the new integer and reallocation fails, the
** function will return 0. Otherwise, it will return 1.
**
** If successful, the function will add the variable at the position of
** vector->end and increment the vector->end pointer and the vector->len
** counter.
*/

int	vector_add(t_vector *vector, int add)
{
	if (!vector)
		return (0);
	if (vector->len + 1 > vector->allocated_mem)
		if (!vector->realloc(vector))
			return (0);
	if (vector->end == NULL)
	{
		vector->end = vector->start;
		*vector->end = add;
	}
	else
		*++vector->end = add;
	vector->len++;
	return (1);
}

/*
** This function destroys a vector object along with its vector. If invalid
** pointers are passed, the function returns 0. Otherwise, memory is freed as
** needed and the function returns 1.
**
** The vector object is zeroed before its memory is freed. The *vector pointer
** is set to NULL after the memory is freed.
*/

int	vector_del(t_vector **vector)
{
	if (vector != NULL && *vector == NULL)
		return (0);
	if ((*vector)->start)
		free((*vector)->start);
	ft_bzero(*vector, sizeof(t_vector));
	*vector = ft_del(*vector);
	return (1);
}

/*
** This function creates a new vector object. If reservation of memory for the
** vector object or the vector itself fails, the function returns NULL and errno
** is set to ENOMEM. Otherwise a pointer to the vector object is returned.
**
** The vector object contains pointers to the start and end of the vector, and
** an index pointer that initially points to the start of the vector. It also
** contains pointers to all remaining vector-related functions, including
** vector->add to add integers to the vector, vector->rem to remove integers
** from the vector, vector->del to delete the vector object and free all memory
** it occupies, and vector->realloc which is used internally to reallocate the
** vector if more memory is needed.
*/

t_vector	*vector_new(void)
{
	t_vector *vector;

	vector = malloc(sizeof(t_vector));
	if (vector != NULL)
	{
		ft_bzero(vector, sizeof(t_vector));
		vector->add = vector_add;
		vector->rem = vector_rem;
		vector->del = vector_del;
		vector->realloc = vector_realloc;
		if (!(vector->realloc(vector)))
			vector = ft_del(vector);
	}
	if (vector == NULL)
		errno = ENOMEM;
	return (vector);
}


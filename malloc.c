/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 10:00:43 by amaindro          #+#    #+#             */
/*   Updated: 2017/08/01 01:59:55 by amaindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc2.h"

pthread_mutex_t		g_mutex = PTHREAD_MUTEX_INITIALIZER;

void				*init(size_t size_max)
{
	t_chunk		*chunk;
	size_t		size;

	size = (size_max + sizeof(t_chunk)) * 100;
	size += getpagesize() - size % getpagesize();
	chunk = mmap(0, size, PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if (chunk == MAP_FAILED)
		return (NULL);
	chunk->is_free = 1;
	chunk->size = size;
	chunk->block = chunk;
	chunk->next = NULL;
	return (chunk);
}

int					get_size(size_t size)
{
	if (size < TINY_ALLOC)
		return (TINY_ALLOC);
	else if (size < SMALL_ALLOC)
		return (SMALL_ALLOC);
	else
		return (size);
}

int					get_chunk(size_t size)
{
	if (size < TINY_ALLOC)
		return (TINY);
	else if (size < SMALL_ALLOC)
		return (SMALL);
	else
		return (LARGE);
}

void				*malloc(size_t size)
{
	void		*ptr;
	int			i;

	ptr = NULL;
	pthread_mutex_lock(&g_mutex);
	i = get_chunk(size);
	if (!chunk_array[i])
		chunk_array[i] = init(get_size(size));
	if (chunk_array[i])
		ptr = allocator(size, get_size(size), chunk_array[i]);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

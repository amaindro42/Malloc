/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 13:02:05 by amaindro          #+#    #+#             */
/*   Updated: 2017/07/07 15:46:59 by amaindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc2.h"

static void			*reallocator(t_chunk *chunk, size_t size)
{
	size_t		old_size;
	void		*old_content;
	void		*content;

	old_size = chunk->size;
	old_content = (void*)((unsigned long long int)chunk + sizeof(t_chunk));
	if (chunk->next && chunk->next->is_free && chunk->block ==
			chunk->next->block)
		chunk_merge(chunk);
	if (chunk->size >= size + sizeof(t_chunk))
	{
		if (chunk->size >= (size + sizeof(t_chunk)) + (sizeof(t_chunk) + 1))
			split(chunk, size);
		return ((void*)((unsigned long long int)chunk + sizeof(t_chunk)));
	}
	chunk->is_free = 1;
	if (chunk->prev && (void *)((unsigned long long int)chunk->prev +
				chunk->prev->size) != chunk)
		munmap(chunk, chunk->size);
	if (!(content = malloc(size)))
		return (NULL);
	return (ft_memmove(content, old_content, old_size));
}

void				*realloc(void *ptr, size_t size)
{
	t_chunk		*chunk;
	int			found;

	pthread_mutex_lock(&g_mutex);
	found = search_in_chunk(ptr, chunk_array[0]) ||
		search_in_chunk(ptr, chunk_array[1]) ||
		search_in_chunk(ptr, chunk_array[2]);
	if (ptr && found)
	{
		chunk = (void *)((unsigned long long int)ptr - sizeof(t_chunk));
		pthread_mutex_unlock(&g_mutex);
		return (reallocator(chunk, size));
	}
	pthread_mutex_unlock(&g_mutex);
	return ((ptr) ? NULL : malloc(size));
}

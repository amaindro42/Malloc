/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 16:11:47 by amaindro          #+#    #+#             */
/*   Updated: 2017/07/27 19:20:36 by amaindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc2.h"

void				*search_in_chunk(t_chunk *ptr, t_chunk *chunk)
{
	while ((void *)((unsigned long long int)ptr - sizeof(t_chunk)) !=
			chunk && chunk)
	{
		chunk = chunk->next;
	}
	return (chunk);
}

void				chunk_merge(t_chunk *chunk)
{
	chunk->size += chunk->next->size;
	chunk->next = chunk->next->next;
	if (chunk->next)
		chunk->next->prev = chunk;
}

static void			chunk_free(t_chunk *chunk)
{
	chunk->is_free = 1;
	if (chunk->prev && chunk->prev->is_free && chunk->block ==
			chunk->prev->block)
	{
		chunk = chunk->prev;
		chunk_merge(chunk);
	}
	if (chunk->next && chunk->next->is_free && chunk->block ==
			chunk->next->block)
		chunk_merge(chunk);
	if (chunk->prev && chunk->block == chunk && (chunk->next == NULL ||
				chunk->next->block != chunk))
	{
		chunk->prev->next = chunk->next;
		if (chunk->next)
			chunk->next->prev = chunk->prev;
		munmap(chunk, chunk->size);
	}
}

void				free(void *ptr)
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
		chunk_free(chunk);
	}
	pthread_mutex_unlock(&g_mutex);
}

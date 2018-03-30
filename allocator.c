/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 14:42:58 by amaindro          #+#    #+#             */
/*   Updated: 2017/07/13 15:01:20 by amaindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc2.h"

void				split(t_chunk *chunk, size_t size)
{
	size_t	tmp_size;
	void	*tmp_next;

	tmp_size = chunk->size;
	tmp_next = chunk->next;
	chunk->size = sizeof(t_chunk) + size;
	chunk->next = (void *)((unsigned long long int)chunk +
			(unsigned long long int)chunk->size);
	chunk->next->size = tmp_size - chunk->size;
	chunk->next->is_free = 1;
	chunk->next->block = chunk;
	chunk->next->next = tmp_next;
	chunk->next->prev = chunk;
	if (chunk->next->next)
		chunk->next->next->prev = chunk->next;
}

void				*allocator(size_t size, size_t size_max, t_chunk *chunk)
{
	while (chunk)
	{
		if (chunk->is_free && chunk->size >= size + sizeof(t_chunk))
		{
			if (chunk->size >= (size + sizeof(t_chunk)) +
					(sizeof(t_chunk) + 1))
				split(chunk, size);
			chunk->is_free = 0;
			return ((void*)((unsigned long long int)chunk +
						sizeof(t_chunk)));
		}
		if (!chunk->next)
			chunk->next = init(size_max);
		if (chunk->next)
			chunk->next->prev = chunk;
		chunk = chunk->next;
	}
	ft_putstr("malloc: no space left on memory\n");
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:00:17 by amaindro          #+#    #+#             */
/*   Updated: 2017/08/01 01:42:42 by amaindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/mman.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <pthread.h>

# define TINY_ALLOC 10000
# define SMALL_ALLOC 150000

struct s_chunk				*chunk_array[3];

extern pthread_mutex_t		g_mutex;

enum						e_type {
	TINY,
	SMALL,
	LARGE
};

typedef struct				s_chunk
{
	size_t			size;
	int				is_free;
	struct s_chunk	*next;
	struct s_chunk	*prev;
	void			*block;
}							t_chunk;

void						*malloc(size_t size);
void						free(void *ptr);
void						*realloc(void *ptr, size_t size);
void						show_alloc_mem(void);
void						hex_dump(void);
void						char_dump(void);
void						*calloc(size_t count, size_t size);
void						*reallocf(void *ptr, size_t size);

#endif

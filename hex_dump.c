/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_dump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 00:54:06 by amaindro          #+#    #+#             */
/*   Updated: 2017/08/01 01:40:37 by amaindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc2.h"

static void				chunk_dump(t_chunk *chunk)
{
	char	*ptr;

	while (chunk != NULL)
	{
		if (!chunk->is_free)
		{
			ft_putaddr((unsigned long long int)chunk, 'a');
			ptr = (char*)((unsigned long long int)chunk + sizeof(t_chunk));
			while (ptr < (char*)((unsigned long long int)chunk + chunk->size))
			{
				ft_putchar(' ');
				ft_putaddr((unsigned char)*ptr, 'a');
				ptr++;
			}
			ft_putchar('\n');
		}
		chunk = chunk->next;
	}
}

static void				chunk_char_dump(t_chunk *chunk)
{
	char	*ptr;

	while (chunk != NULL)
	{
		if (!chunk->is_free)
		{
			ft_putaddr((unsigned long long int)chunk, 'a');
			ptr = (char*)((unsigned long long int)chunk + sizeof(t_chunk));
			ft_putchar(' ');
			while (ptr < (char*)((unsigned long long int)chunk + chunk->size))
			{
				if (ft_isprint(*ptr))
					ft_putchar(*ptr);
				else
					ft_putchar('.');
				ptr++;
			}
			ft_putchar('\n');
		}
		chunk = chunk->next;
	}
}

void					char_dump(void)
{
	chunk_char_dump(chunk_array[0]);
	chunk_char_dump(chunk_array[1]);
	chunk_char_dump(chunk_array[2]);
}

void					hex_dump(void)
{
	chunk_dump(chunk_array[0]);
	chunk_dump(chunk_array[1]);
	chunk_dump(chunk_array[2]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 12:32:40 by amaindro          #+#    #+#             */
/*   Updated: 2018/03/30 17:18:12 by amaindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc2.h"

unsigned long long int	ft_len(unsigned long long int n)
{
	unsigned long long int	i;

	i = 1;
	if (n == 0)
		return (16);
	while (n != 0)
	{
		n /= 16;
		i *= 16;
	}
	return (i);
}

void					ft_putaddr(unsigned long long int n, char c)
{
	unsigned long long int	length;
	unsigned long long int	tmp;

	length = ft_len(n);
	while (length >= 16)
	{
		tmp = (n / (length / 16)) % 16;
		ft_putchar((tmp < 10) ? tmp + '0' : tmp - 10 + c);
		length /= 16;
	}
}

static size_t			print_chunk(t_chunk *chunk)
{
	size_t		total_size;

	total_size = 0;
	while (chunk != NULL)
	{
		if (!chunk->is_free)
		{
			ft_putstr("0x");
			ft_putaddr((unsigned long long int)chunk, 'A');
			ft_putstr(" - ");
			ft_putstr("0x");
			ft_putaddr((unsigned long long int)chunk +
						(unsigned long long int)chunk->size, 'A');
			ft_putstr(" : ");
			ft_putnbr(chunk->size);
			ft_putstr(" octets\n");
			total_size += chunk->size;
		}
		chunk = chunk->next;
	}
	return (total_size);
}

static size_t			printer(t_chunk *chunk, char *str, size_t total_size)
{
	ft_putstr(str);
	ft_putstr("0x");
	ft_putaddr((unsigned long long int)chunk, 'A');
	ft_putchar('\n');
	return (total_size + print_chunk(chunk));
}

void					show_alloc_mem(void)
{
	size_t		total_size;

	total_size = 0;
	pthread_mutex_lock(&g_mutex);
	if (chunk_array[0])
		total_size = printer(chunk_array[0], "TINY : ", total_size);
	if (chunk_array[1])
		total_size = printer(chunk_array[1], "SMALL : ", total_size);
	if (chunk_array[2])
		total_size = printer(chunk_array[2], "LARGE : ", total_size);
	ft_putstr("Total : ");
	ft_putnbr(total_size / 256);
	ft_putchar('\n');
	pthread_mutex_unlock(&g_mutex);
}

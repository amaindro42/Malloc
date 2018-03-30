/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 14:00:51 by amaindro          #+#    #+#             */
/*   Updated: 2017/07/16 18:20:19 by amaindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC2_H
# define MALLOC2_H

# include "malloc.h"

void						*allocator(size_t size, size_t size_max,
		t_chunk *chunk);
void						*init(size_t size_max);
int							get_size(size_t size);
int							get_chunk(size_t size);
void						*search_in_chunk(t_chunk *ptr, t_chunk *chunk);
void						chunk_merge(t_chunk *chunk);
void						split(t_chunk *chunk, size_t size);
unsigned long long int		ft_len(unsigned long long int n);
void						ft_putaddr(unsigned long long int n, char c);

#endif

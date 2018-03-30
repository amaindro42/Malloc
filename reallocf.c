/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 18:01:07 by amaindro          #+#    #+#             */
/*   Updated: 2017/07/16 18:03:10 by amaindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc2.h"

void				*reallocf(void *ptr, size_t size)
{
	void	*content;

	if (!(content = realloc(ptr, size)))
		free(ptr);
	return (content);
}

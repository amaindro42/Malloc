/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 18:37:15 by amaindro          #+#    #+#             */
/*   Updated: 2017/07/16 17:48:57 by amaindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc2.h"

void				*calloc(size_t count, size_t size)
{
	void	*str;

	str = malloc(count * size);
	ft_bzero(str, count * size);
	return (str);
}

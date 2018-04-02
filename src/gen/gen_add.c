/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 21:06:44 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 21:07:07 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen.h"

bool		gen_add(t_gen *gen, void *elem)
{
	int size;

	size = *((int *)elem);
	if (!(gen->mem = ft_memrealloc(gen->mem, gen->mem_size, \
									gen->mem_size + size)))
		return (false);
	ft_memcpy(gen->mem + gen->mem_size, elem, size);
	gen->mem_size += size;
	gen->length++;
	return (true);
}

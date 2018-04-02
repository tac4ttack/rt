/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_remove_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 21:06:53 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 21:06:54 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen.h"

static bool	gen_remove_index_0(t_gen *gen, const int current_mem_size)
{
	void			*tmp;

	gen->mem_size -= current_mem_size;
	tmp = gen->mem;
	if (!gen->length)
		gen->mem = NULL;
	else
		gen->mem = ft_memnew(gen->mem + current_mem_size, gen->mem_size);
	gen->length--;
	if (tmp)
		ft_memdel((void**)&tmp);
	if (!gen->mem)
		return (false);
	return (true);
}

static bool	gen_remove_index_other(t_gen *gen,
										const int current_mem_size,
										const size_t mem_index)
{
	void			*tmp;

	gen->mem_size -= current_mem_size;
	gen->length--;
	tmp = gen->mem;
	if (!(gen->mem = ft_memalloc(gen->mem_size)))
	{
		gen->mem = tmp;
		return (false);
	}
	ft_memcpy(gen->mem, tmp, mem_index);
	ft_memcpy(gen->mem + mem_index,
				tmp + mem_index + current_mem_size,
				gen->mem_size - mem_index);
	return (true);
}

bool		gen_remove_index(t_gen *gen, size_t remove_index)
{
	size_t			mem_index;
	int				*current_mem_size;
	size_t			unit_index;

	if (remove_index >= gen->length)
		return (false);
	current_mem_size = gen->mem;
	if (!remove_index)
		return (gen_remove_index_0(gen, *current_mem_size));
	mem_index = 0;
	unit_index = 0;
	while (mem_index < gen->mem_size)
	{
		current_mem_size = (int *)(gen->mem + mem_index);
		if (unit_index == remove_index)
		{
			return (gen_remove_index_other(gen,
											*current_mem_size, mem_index));
		}
		mem_index += *current_mem_size;
		unit_index++;
	}
	return (false);
}

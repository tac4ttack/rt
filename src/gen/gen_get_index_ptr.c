/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_get_index_ptr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 21:06:49 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 21:07:45 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen.h"

void		*gen_get_index_ptr(t_gen *gen, int index)
{
	size_t			mem_index;
	int				current_index;
	int				*current_mem_size;

	mem_index = 0;
	current_index = 0;
	while (mem_index < gen->mem_size)
	{
		if (index == current_index)
			return (gen->mem + mem_index);
		current_mem_size = (int *)(gen->mem + mem_index);
		mem_index += *current_mem_size;
		current_index++;
	}
	return (NULL);
}

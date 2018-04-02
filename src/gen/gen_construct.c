/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_construct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 21:06:46 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 21:07:15 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen.h"

void		*gen_construct(void)
{
	t_gen *gen;

	if (!(gen = ft_memalloc(sizeof(t_gen))))
		return (NULL);
	gen->add = &gen_add;
	gen->remove_mem_index = &gen_remove_mem_index;
	gen->remove_index = &gen_remove_index;
	gen->print = &gen_print;
	return (gen);
}

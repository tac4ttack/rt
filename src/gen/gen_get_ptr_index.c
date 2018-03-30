/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_get_ptr_index.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 21:06:50 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 21:08:09 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen.h"

int			gen_get_ptr_index(t_gen *gen, void *obj)
{
	void	*tmp;
	int		res;

	tmp = obj;
	res = 0;
	if (obj == gen->mem)
		return (res);
	else
	{
		tmp = gen->mem;
		while (tmp != obj)
		{
			tmp = tmp + *(int*)(tmp);
			res++;
		}
	}
	return (res);
}

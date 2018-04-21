/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_destruct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 21:06:48 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/21 20:37:10 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen.h"

void		*gen_destruct(t_gen **gen)
{
	if (gen && *gen)
	{
		if ((*gen)->mem)
			free((*gen)->mem);
		ft_memdel((void **)gen);
	}
	return (NULL);
}

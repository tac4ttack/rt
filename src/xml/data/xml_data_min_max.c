/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_data_min_max.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 12:32:27 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/08 05:46:34 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	xml_data_min_max(t_env *e, char **attributes, int *i, t_float3 *f)
{
	if (f && attributes && e)
	{
		if (attributes[(*i)] == NULL)
			s_error("\x1b[1;31mError reading MINMAX value\x1b[0m", e);
		f->x = ft_atof(attributes[(*i)++] + 5);
		f->y = ft_atof(attributes[(*i)++]);
		if (attributes[(*i)][ft_strlen(attributes[*i]) - 1] != '\"')
			s_error("\x1b[1;31mError in MINMAX vector from scene\x1b[0m", e);
		f->z = ft_atof(attributes[(*i)++]);
	}
	else
		s_error("\x1b[1;31mError reading MINMAX vector from scene\x1b[0m", e);
}

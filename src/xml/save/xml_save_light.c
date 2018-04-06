/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 20:37:26 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/06 20:37:53 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_write_light_data(t_light *light, int fd)
{
	ft_putstr_fd("\t<light\n", fd);
	xml_write_int("\ttype", light->type, fd);
	xml_write_float3("\tpos", light->pos, fd);
	xml_write_float3("\tdir", light->dir, fd);
	xml_write_float("\tbrightness", light->brightness, fd);
	xml_write_int("\tshrink", light->shrink, fd);
	xml_write_color(light->color, fd);
	ft_putstr_fd("/>\n", fd);
}

void		xml_write_lights(t_env *e, const int fd)
{
	t_gen	*gen;
	t_light	*light;
	size_t	mem_index;
	size_t	index;

	mem_index = 0;
	index = 0;
	gen = e->gen_lights;
	while (mem_index < gen->mem_size)
	{
		light = gen->mem + mem_index;
		xml_write_light_data(light, fd);
		mem_index += *((int *)(gen->mem + mem_index));
		index++;
	}
}

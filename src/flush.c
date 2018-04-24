/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 21:57:55 by adalenco          #+#    #+#             */
/*   Updated: 2018/04/21 21:57:56 by adalenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			flush_scene(t_env *e)
{
	ft_memdel((void**)&e->cameras);
	ft_putendl("\x1b[1;29mFreed cameras array\x1b[0m");
	ft_memdel((void**)&e->scene);
	ft_putendl("\x1b[1;29mFreed scene datas\x1b[0m");
	ft_memdel((void**)&e->pixel_data);
	ft_putendl("\x1b[1;29mFreed pixel buffer\x1b[0m");
	ft_memdel((void**)&e->ui);
	ft_putendl("\x1b[1;29mFreed UI environnement\x1b[0m");
	ft_memdel((void**)&e);
	ft_putendl("\x1b[1;29mFreed RT environnement\x1b[0m");
}

void			flush_ui_xml(t_env *e)
{
	if (e->ui)
	{
		if (e->ui->pixbuf)
			g_object_unref(e->ui->pixbuf);
		if (e->ui->surface)
			cairo_surface_destroy(e->ui->surface);
		if (e->ui->error)
			g_error_free(e->ui->error);
		ft_memdel((void**)&e->ui);
		ft_putendl("\x1b[1;29mFreed UI environnement\x1b[0m");
	}
	if (e->xml)
	{
		if (e->xml->nodes)
			xml_node_clean(&e->xml->nodes);
		if (e->xml->sub_node)
			xml_node_clean(&e->xml->sub_node);
	}
	ft_memdel((void**)&e->xml);
	ft_putendl("\x1b[1;29mFreed XML ressources\x1b[0m");
}

void			flush(t_env *e)
{
	int			i;

	if (e->textures)
	{
		i = 0;
		if (e->textures)
			while (i < 5)
			{
				texture_destroy(e, &e->textures[i]);
				i++;
			}
		ft_memdel((void**)&e->textures);
	}
	cuda_destruct(&e->cuda);
	gen_destruct(&e->gen_objects);
	gen_destruct(&e->gen_lights);
	flush_ui_xml(e);
	flush_scene(e);
}

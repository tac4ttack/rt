/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 17:43:38 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/13 16:32:38 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void	xml_write_scene_res(int width, int height, int fd)
{
	ft_putstr_fd("res=\"", fd);
	ft_putstr_fd(ft_itoa(width), fd);
	ft_putstr_fd(", ", fd);
	ft_putstr_fd(ft_itoa(height), fd);
	ft_putstr_fd("\" ", fd);
}

static void	xml_write_scene_ambient(FT_FLOAT3 ambient, int fd)
{
	ft_putstr_fd("ambient=\"", fd);
	ft_putstr_fd(ft_ftoa(ambient.x), fd);
	ft_putstr_fd(", ", fd);
	ft_putstr_fd(ft_ftoa(ambient.y), fd);
	ft_putstr_fd(", ", fd);
	ft_putstr_fd(ft_ftoa(ambient.z), fd);
	ft_putstr_fd("\">\n", fd);
}

static void			xml_write_objects(t_env *e, int fd)
{
	t_gen			*gen;
	t_object		*obj;
	size_t			mem_index;
	size_t			index;

	mem_index = 0;
	index = 0;
	gen = e->gen_objects;
	while (index < gen->length)
	{
		obj = gen->mem + mem_index;
		if (obj->type == OBJ_CONE)
			xml_write_cone((t_cone *)obj, fd);
		else if (obj->type == OBJ_CYLINDER)
			xml_write_cylinder((t_cylinder *)obj, fd);
		else if (obj->type == OBJ_ELLIPSOID)
			xml_write_ellipsoid((t_ellipsoid *)obj, fd);
		else if (obj->type == OBJ_PLANE)
			xml_write_plane((t_plane *)obj, fd);
		else if (obj->type == OBJ_SPHERE)
			xml_write_sphere((t_sphere *)obj, fd);
		else if (obj->type == OBJ_TORUS)
			xml_write_torus((t_torus *)obj, fd);
		mem_index += *((int *)(gen->mem + mem_index));
		index++;
	}
}

void			xml_save_scene(t_env *e, char *filename)
{
	int			fd;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC);
	ft_putstr_fd("<?xml version=\"1.0\"?>\n<scene\t", fd);
	xml_write_scene_res(e->scene->win_w, e->scene->win_h, fd);
	xml_write_scene_ambient(e->scene->ambient, fd);
	xml_write_cameras(e, fd, e->cameras);
	xml_write_lights(e, fd);
	xml_write_objects(e, fd);
	ft_putstr_fd("</scene>\n", fd);
	fchmod(fd, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
	close(fd);
}

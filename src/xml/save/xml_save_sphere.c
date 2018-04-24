/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 20:39:15 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/21 23:26:18 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	xml_write_sphere(t_sphere *sphere, const int fd)
{
	ft_putstr_fd("\t<sphere\n", fd);
	xml_write_float3("\tpos", sphere->pos, fd);
	xml_write_float3("\tdir", sphere->dir, fd);
	xml_write_float("\tradius", sphere->radius, fd);
	xml_write_color(sphere->color, fd);
	xml_write_float3("\tdiff", sphere->diff, fd);
	xml_write_float3("\tspec", sphere->spec, fd);
	xml_write_float("\treflex", sphere->reflex, fd);
	xml_write_float("\trefract", sphere->refract, fd);
	xml_write_float("\topacity", sphere->opacity, fd);
	xml_write_float3("\tp_limit_pos", sphere->limit_pos, fd);
	xml_write_float3("\tp_limit_dir", sphere->limit_dir, fd);
	xml_write_float3("\tmin", sphere->cut_min, fd);
	xml_write_float3("\tmax", sphere->cut_max, fd);
	xml_write_flags(sphere->flags, fd);
	ft_putstr_fd("/>\n", fd);
}

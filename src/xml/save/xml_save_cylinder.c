/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 20:35:02 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/06 20:48:19 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	xml_write_cylinder(t_cylinder *cyl, const int fd)
{
	ft_putstr_fd("\t<cylinder\n", fd);
	xml_write_float3("\tpos", cyl->pos, fd);
	xml_write_float3("\tdir", cyl->dir, fd);
	xml_write_float("\tradius", cyl->radius, fd);
	xml_write_color(cyl->color, fd);
	xml_write_float("\theight", cyl->height, fd);
	xml_write_float3("\tdiff", cyl->diff, fd);
	xml_write_float3("\tspec", cyl->spec, fd);
	xml_write_float("\treflex", cyl->reflex, fd);
	xml_write_float("\trefract", cyl->refract, fd);
	xml_write_float("\topacity", cyl->opacity, fd);
	xml_write_float3("\tp_limit_pos", cyl->limit_pos, fd);
	xml_write_float3("\tp_limit_dir", cyl->limit_dir, fd);
	xml_write_flags(cyl->flags, fd);
	ft_putstr_fd("/>\n", fd);
}

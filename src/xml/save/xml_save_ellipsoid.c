/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_ellipsoid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 20:38:01 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/06 20:38:31 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	xml_write_ellipsoid(t_ellipsoid *elli, const int fd)
{
	ft_putstr_fd("\t<ellipsoid\n", fd);
	xml_write_float3("\tpos", elli->pos, fd);
	xml_write_float3("\tdir", elli->dir, fd);
	xml_write_float("\tradius", elli->radius, fd);
	xml_write_float3("\taxis_size", elli->axis_size, fd);
	xml_write_color(elli->color, fd);
	xml_write_float3("\tdiff", elli->diff, fd);
	xml_write_float3("\tspec", elli->spec, fd);
	xml_write_float("\treflex", elli->reflex, fd);
	xml_write_float("\trefract", elli->refract, fd);
	xml_write_float("\topacity", elli->opacity, fd);
	xml_write_float3("\tp_limit_pos", elli->limit_pos, fd);
	xml_write_float3("\tp_limit_dir", elli->limit_dir, fd);
	xml_write_flags(elli->flags, fd);
	ft_putstr_fd("/>\n", fd);
}

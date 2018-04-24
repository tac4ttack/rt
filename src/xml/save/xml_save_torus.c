/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_torus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 20:39:15 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/21 23:26:25 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	xml_write_torus(t_torus *torus, const int fd)
{
	ft_putstr_fd("\t<torus\n", fd);
	xml_write_float3("\tpos", torus->pos, fd);
	xml_write_float3("\tdir", torus->dir, fd);
	xml_write_float("\tlil_radius", torus->lil_radius, fd);
	xml_write_float("\tbig_radius", torus->big_radius, fd);
	xml_write_color(torus->color, fd);
	xml_write_float3("\tdiff", torus->diff, fd);
	xml_write_float3("\tspec", torus->spec, fd);
	xml_write_float("\treflex", torus->reflex, fd);
	xml_write_float("\trefract", torus->refract, fd);
	xml_write_float("\topacity", torus->opacity, fd);
	xml_write_float3("\tp_limit_pos", torus->limit_pos, fd);
	xml_write_float3("\tp_limit_dir", torus->limit_dir, fd);
	xml_write_float3("\tmin", torus->cut_min, fd);
	xml_write_float3("\tmax", torus->cut_max, fd);
	xml_write_flags(torus->flags, fd);
	ft_putstr_fd("/>\n", fd);
}

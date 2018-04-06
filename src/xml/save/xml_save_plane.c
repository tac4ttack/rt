/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 20:38:39 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/06 20:38:55 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	xml_write_plane(t_plane *plane, const int fd)
{
	ft_putstr_fd("\t<plane\n", fd);
	xml_write_float3("\tpos", plane->pos, fd);
	xml_write_float3("\tnormale", plane->normal, fd);
	xml_write_color(plane->color, fd);
	xml_write_float3("\tdiff", plane->diff, fd);
	xml_write_float3("\tspec", plane->spec, fd);
	xml_write_float("\treflex", plane->reflex, fd);
	xml_write_float("\trefract", plane->refract, fd);
	xml_write_float("\topacity", plane->opacity, fd);
	xml_write_float("\tradius", plane->radius, fd);
	xml_write_float3("\tp_limit_pos", plane->limit_pos, fd);
	xml_write_float3("\tp_limit_dir", plane->limit_dir, fd);
	xml_write_flags(plane->flags, fd);
	ft_putstr_fd("/>\n", fd);
}

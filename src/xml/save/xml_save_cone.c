/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_cone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 20:35:37 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/06 20:36:17 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	xml_write_cone(t_cone *cone, const int fd)
{
	ft_putstr_fd("\t<cone\n", fd);
	xml_write_float3("\tpos", cone->pos, fd);
	xml_write_float3("\tdir", cone->dir, fd);
	xml_write_float("\tangle", cone->angle, fd);
	xml_write_color(cone->color, fd);
	xml_write_float3("\tdiff", cone->diff, fd);
	xml_write_float3("\tspec", cone->spec, fd);
	xml_write_float("\treflex", cone->reflex, fd);
	xml_write_float("\trefract", cone->refract, fd);
	xml_write_float("\topacity", cone->opacity, fd);
	xml_write_float3("\tp_limit_pos", cone->limit_pos, fd);
	xml_write_float3("\tp_limit_dir", cone->limit_dir, fd);
	xml_write_flags(cone->flags, fd);
	ft_putstr_fd("/>\n", fd);
}


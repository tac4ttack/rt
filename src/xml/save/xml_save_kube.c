/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_kube.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:08:58 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/21 23:26:02 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	xml_write_kube(t_kube *kube, const int fd)
{
	ft_putstr_fd("\t<kube\n", fd);
	xml_write_float3("\tpos", kube->pos, fd);
	xml_write_float3("\tdir", kube->dir, fd);
	xml_write_float("\toption", kube->option, fd);
	xml_write_color(kube->color, fd);
	xml_write_float3("\tdiff", kube->diff, fd);
	xml_write_float3("\tspec", kube->spec, fd);
	xml_write_float("\treflex", kube->reflex, fd);
	xml_write_float("\trefract", kube->refract, fd);
	xml_write_float("\topacity", kube->opacity, fd);
	xml_write_float3("\tp_limit_pos", kube->limit_pos, fd);
	xml_write_float3("\tp_limit_dir", kube->limit_dir, fd);
	xml_write_float3("\tmin", kube->cut_min, fd);
	xml_write_float3("\tmax", kube->cut_max, fd);
	xml_write_flags(kube->flags, fd);
	ft_putstr_fd("/>\n", fd);
}

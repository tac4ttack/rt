/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_add_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:59:59 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/19 15:09:05 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		ui_add_cone_effects(t_cone *cone)
{
	cone->limit_pos.x = 0;
	cone->limit_pos.y = 0;
	cone->limit_pos.z = 0;
	cone->limit_dir.x = 0;
	cone->limit_dir.y = 0;
	cone->limit_dir.z = 0;
	cone->waves_p1.x = 0.8;
	cone->waves_p1.y = 0.8;
	cone->waves_p1.z = 0.8;
	cone->waves_p2.x = 5;
	cone->waves_p2.y = 5;
	cone->waves_p2.z = 5;
	cone->check_size.x = 20;
	cone->check_size.y = 10;
	cone->diff_map_id = -1;
	cone->diff_offset.x = 0;
	cone->diff_offset.y = 0;
	cone->diff_ratio.x = 1;
	cone->diff_ratio.y = 1;
	cone->u_axis = cross_vect(cone->dir);
}

void			ui_add_cone(t_env *e)
{
	t_cone cone;

	cone.size = sizeof(t_cone);
	cone.type = OBJ_CONE;
	cone.id = e->gen_objects->length;
	cone.pos.x = 0;
	cone.pos.y = 0;
	cone.pos.z = 0;
	cone.flags = 0;
	cone.dir = cone.pos;
	cone.dir.z = 1;
	cone.angle = 4;
	cone.color = rand();
	cone.diff.x = 0.42;
	cone.diff.y = 0.42;
	cone.diff.z = 0.42;
	cone.spec = cone.diff;
	cone.reflex = 0;
	cone.refract = 0;
	cone.opacity = 1;
	ui_add_cone_effects(&cone);
	e->gen_objects->add(e->gen_objects, (void*)&cone);
}

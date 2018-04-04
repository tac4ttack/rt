/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_add_ellipsoid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:59:54 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/04 11:07:50 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ui_add_ellipsoid_effects(t_ellipsoid *ellipsoid)
{
	ellipsoid->limit_pos.x = 0;
	ellipsoid->limit_pos.y = 0;
	ellipsoid->limit_pos.z = 0;
	ellipsoid->limit_dir.x = 0;
	ellipsoid->limit_dir.y = 0;
	ellipsoid->limit_dir.z = 0;
	ellipsoid->waves_p1.x = 0.8;
	ellipsoid->waves_p1.y = 0.8;
	ellipsoid->waves_p1.z = 0.8;
	ellipsoid->waves_p2.x = 5;
	ellipsoid->waves_p2.y = 5;
	ellipsoid->waves_p2.z = 5;
	ellipsoid->check_size.x = 20;
	ellipsoid->check_size.y = 10;
	ellipsoid->diff_map_id = -1;
	ellipsoid->diff_offset.x = 0;
	ellipsoid->diff_offset.y = 0;
	ellipsoid->diff_ratio.x = 1;
	ellipsoid->diff_ratio.y = 1;
}

void	ui_add_ellipsoid(t_env *e)
{
	t_ellipsoid ellipsoid;

	ellipsoid.size = sizeof(t_ellipsoid);
	ellipsoid.id = e->gen_objects->length;
	ellipsoid.type = OBJ_ELLIPSOID;
	ellipsoid.pos.x = 0;
	ellipsoid.pos.y = 0;
	ellipsoid.pos.z = 0;
	ellipsoid.dir = ellipsoid.pos;
	ellipsoid.dir.z = 1;
	ellipsoid.flags = 0;
	ellipsoid.radius = 1;
	ellipsoid.color = rand();
	ellipsoid.diff.x = 0.42;
	ellipsoid.diff.y = 0.42;
	ellipsoid.diff.z = 0.42;
	ellipsoid.spec = ellipsoid.diff;
	ellipsoid.reflex = 0;
	ellipsoid.refract = 0;
	ellipsoid.opacity = 1;
	ellipsoid.axis_size.x = 2;
	ellipsoid.axis_size.y = 1;
	ellipsoid.axis_size.z = 2;
	ui_add_ellipsoid_effects(&ellipsoid);
	e->gen_objects->add(e->gen_objects, (void*)&ellipsoid);
}

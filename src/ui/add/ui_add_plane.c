/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_add_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:59:52 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/05 18:23:32 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ui_add_plane_effects(t_plane *plane)
{
	plane->limit_pos.x = 0;
	plane->limit_pos.y = 0;
	plane->limit_pos.z = 0;
	plane->limit_dir.x = 0;
	plane->limit_dir.y = 0;
	plane->limit_dir.z = 0;
	plane->waves_p1.x = 0.8;
	plane->waves_p1.y = 0.8;
	plane->waves_p1.z = 0.8;
	plane->waves_p2.x = 5;
	plane->waves_p2.y = 5;
	plane->waves_p2.z = 5;
	plane->check_size.x = 10;
	plane->check_size.y = 10;
	plane->diff_map_id = -1;
	plane->diff_offset.x = 0;
	plane->diff_offset.y = 0;
	plane->diff_ratio.x = 1;
	plane->diff_ratio.y = 1;
}

void	ui_add_plane(t_env *e)
{
	t_plane plane;

	plane.size = sizeof(t_plane);
	plane.id = e->gen_objects->length;
	plane.type = OBJ_PLANE;
	plane.pos.x = 0;
	plane.pos.y = 0;
	plane.pos.z = 0;
	plane.flags = 0;
	plane.normal = plane.pos;
	plane.normal.z = 1;
	plane.color = rand();
	plane.diff.x = 0.42;
	plane.diff.y = 0.42;
	plane.diff.z = 0.42;
	plane.spec = plane.diff;
	plane.reflex = 0;
	plane.refract = 0;
	plane.opacity = 1;
	plane.radius = 0;
	ui_add_plane_effects(&plane);
	e->gen_objects->add(e->gen_objects, (void*)&plane);
}

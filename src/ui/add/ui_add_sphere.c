/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_add_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:59:42 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/19 15:09:05 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		ui_add_sphere_effects(t_sphere *sphere)
{
	sphere->limit_pos.x = 0;
	sphere->limit_pos.y = 0;
	sphere->limit_pos.z = 0;
	sphere->limit_dir.x = 0;
	sphere->limit_dir.y = 0;
	sphere->limit_dir.z = 0;
	sphere->waves_p1.x = 0.8;
	sphere->waves_p1.y = 0.8;
	sphere->waves_p1.z = 0.8;
	sphere->waves_p2.x = 5;
	sphere->waves_p2.y = 5;
	sphere->waves_p2.z = 5;
	sphere->check_size.x = 20;
	sphere->check_size.y = 10;
	sphere->diff_map_id = -1;
	sphere->diff_offset.x = 0;
	sphere->diff_offset.y = 0;
	sphere->diff_ratio.x = 1;
	sphere->diff_ratio.y = 1;
}

void			ui_add_sphere(t_env *e)
{
	t_sphere sphere;

	sphere.size = sizeof(t_sphere);
	sphere.id = e->gen_objects->length;
	sphere.type = OBJ_SPHERE;
	sphere.pos.x = 0;
	sphere.pos.y = 0;
	sphere.flags = 0;
	sphere.pos.z = 0;
	sphere.dir = sphere.pos;
	sphere.dir.z = 1;
	sphere.radius = 4;
	sphere.color = rand();
	sphere.diff.x = 0.42;
	sphere.diff.y = 0.42;
	sphere.diff.z = 0.42;
	sphere.spec = sphere.diff;
	sphere.reflex = 0;
	sphere.refract = 0;
	sphere.opacity = 1;
	ui_add_sphere_effects(&sphere);
	e->gen_objects->add(e->gen_objects, (void*)&sphere);
}

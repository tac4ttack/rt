/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_add_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:59:56 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/19 15:09:05 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		ui_add_cylinder_effects(t_cylinder *cylinder)
{
	cylinder->reflex = 0;
	cylinder->refract = 0;
	cylinder->opacity = 1;
	cylinder->limit_pos.x = 0;
	cylinder->limit_pos.y = 0;
	cylinder->limit_pos.z = 0;
	cylinder->limit_dir.x = 0;
	cylinder->limit_dir.y = 0;
	cylinder->limit_dir.z = 0;
	cylinder->waves_p1.x = 0.8;
	cylinder->waves_p1.y = 0.8;
	cylinder->waves_p1.z = 0.8;
	cylinder->waves_p2.x = 5;
	cylinder->waves_p2.y = 5;
	cylinder->waves_p2.z = 5;
	cylinder->check_size.x = 20;
	cylinder->check_size.y = 10;
	cylinder->diff_map_id = -1;
	cylinder->diff_offset.x = 0;
	cylinder->diff_offset.y = 0;
	cylinder->diff_ratio.x = 1;
	cylinder->diff_ratio.y = 1;
	cylinder->u_axis = cross_vect(cylinder->dir);
}

void			ui_add_cylinder(t_env *e)
{
	t_cylinder cylinder;

	cylinder.size = sizeof(t_cylinder);
	cylinder.id = e->gen_objects->length;
	cylinder.type = OBJ_CYLINDER;
	cylinder.pos.x = 0;
	cylinder.pos.y = 0;
	cylinder.pos.z = 0;
	cylinder.dir = cylinder.pos;
	cylinder.dir.z = 1;
	cylinder.dir = normalize_vect(cylinder.dir);
	cylinder.radius = 1;
	cylinder.flags = 0;
	cylinder.color = rand();
	cylinder.diff.x = 0.42;
	cylinder.diff.y = 0.42;
	cylinder.diff.z = 0.42;
	cylinder.spec = cylinder.diff;
	ui_add_cylinder_effects(&cylinder);
	e->gen_objects->add(e->gen_objects, (void*)&cylinder);
}

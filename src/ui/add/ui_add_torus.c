/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_add_torus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:59:37 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/14 19:13:47 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		ui_add_torus_effects(t_torus *torus)
{
	torus->limit_pos.x = 0;
	torus->limit_pos.y = 0;
	torus->limit_pos.z = 0;
	torus->limit_dir.x = 0;
	torus->limit_dir.y = 0;
	torus->limit_dir.z = 0;
	torus->waves_p1.x = 0.8;
	torus->waves_p1.y = 0.8;
	torus->waves_p1.z = 0.8;
	torus->waves_p2.x = 5;
	torus->waves_p2.y = 5;
	torus->waves_p2.z = 5;
	torus->check_size.x = 20;
	torus->check_size.y = 10;
	torus->diff_map_id = -1;
	torus->diff_offset.x = 0;
	torus->diff_offset.y = 0;
	torus->diff_ratio.x = 1;
	torus->diff_ratio.y = 1;
}

void			ui_add_torus(t_env *e)
{
	t_torus torus;

	torus.size = sizeof(t_torus);
	torus.id = e->gen_objects->length;
	torus.type = OBJ_TORUS;
	torus.pos.x = 0;
	torus.pos.y = 0;
	torus.pos.z = 0;
	torus.flags = 0;
	torus.dir = torus.pos;
	torus.dir.y = 1;
	torus.lil_radius = 2;
	torus.big_radius = 5;
	torus.color = rand();
	torus.diff.x = 0.42;
	torus.diff.y = 0.42;
	torus.diff.z = 0.42;
	torus.spec = torus.diff;
	torus.reflex = 0;
	torus.refract = 0;
	torus.opacity = 1;
	ui_add_torus_effects(&torus);
	e->gen_objects->add(e->gen_objects, (void*)&torus);
}

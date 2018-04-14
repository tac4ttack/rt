/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_push_torus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 18:27:16 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/14 18:32:33 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_push_torus_effects(t_torus *torus)
{
	torus->waves_p1.x = 0.8;
	torus->waves_p1.y = 0.8;
	torus->waves_p1.z = 0.8;
	torus->waves_p2.x = 5;
	torus->waves_p2.y = 5;
	torus->waves_p2.z = 5;
	torus->check_size.x = 1;
	torus->check_size.y = 1;
	torus->diff_map_id = -1;
	torus->diff_offset.x = 0;
	torus->diff_offset.y = 0;
	torus->diff_ratio.x = 1;
	torus->diff_ratio.y = 1;
	torus->cut_min.x = 0;
	torus->cut_min.y = 0;
	torus->cut_min.z = 0;
	torus->cut_max.x = 0;
	torus->cut_max.y = 0;
	torus->cut_max.z = 0;
}

void		xml_push_torus(t_env *e, t_node *list)
{
	t_torus torus;

	torus.size = sizeof(t_torus);
	torus.id = e->current_index_objects;
	torus.type = OBJ_TORUS;
	torus.pos = list->pos;
	torus.dir = list->dir;
	torus.lil_radius = list->radius;
	torus.big_radius = list->radius2;
	torus.color = list->color;
	torus.diff = list->diff;
	torus.spec = list->spec;
	torus.reflex = list->reflex;
	torus.refract = list->refract;
	torus.opacity = list->opacity;
	torus.limit_pos = list->limit_pos;
	torus.limit_dir = list->limit_dir;
	torus.flags = list->flags;
	xml_push_torus_effects(&torus);
	e->gen_objects->add(e->gen_objects, (void*)&torus);
}

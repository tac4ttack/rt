/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_push_ellipsoid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 18:26:29 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/19 15:09:05 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_push_ellipsoid_effects(t_ellipsoid *ellipsoid)
{
	ellipsoid->waves_p1.x = 0.8;
	ellipsoid->waves_p1.y = 0.8;
	ellipsoid->waves_p1.z = 0.8;
	ellipsoid->waves_p2.x = 5;
	ellipsoid->waves_p2.y = 5;
	ellipsoid->waves_p2.z = 5;
	ellipsoid->check_size.x = 1;
	ellipsoid->check_size.y = 1;
	ellipsoid->diff_map_id = -1;
	ellipsoid->diff_offset.x = 0;
	ellipsoid->diff_offset.y = 0;
	ellipsoid->diff_ratio.x = 1;
	ellipsoid->diff_ratio.y = 1;
	ellipsoid->cut_min.x = 0;
	ellipsoid->cut_min.y = 0;
	ellipsoid->cut_min.z = 0;
	ellipsoid->cut_max.x = 0;
	ellipsoid->cut_max.y = 0;
	ellipsoid->cut_max.z = 0;
}

void		xml_push_ellipsoid(t_env *e, t_node *list)
{
	t_ellipsoid ellipsoid;

	ellipsoid.size = sizeof(t_ellipsoid);
	ellipsoid.id = e->current_index_objects;
	ellipsoid.type = OBJ_ELLIPSOID;
	ellipsoid.flags = 0;
	ellipsoid.pos = list->pos;
	ellipsoid.dir = list->dir;
	ellipsoid.radius = list->radius;
	ellipsoid.color = list->color;
	ellipsoid.diff = list->diff;
	ellipsoid.spec = list->spec;
	ellipsoid.reflex = list->reflex;
	ellipsoid.refract = list->refract;
	ellipsoid.opacity = list->opacity;
	ellipsoid.axis_size = list->axis_size;
	ellipsoid.limit_pos = list->limit_pos;
	ellipsoid.limit_dir = list->limit_dir;
	ellipsoid.flags = list->flags;
	xml_push_ellipsoid_effects(&ellipsoid);
	e->gen_objects->add(e->gen_objects, (void*)&ellipsoid);
}

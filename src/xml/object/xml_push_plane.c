/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_push_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 18:28:13 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/14 18:31:11 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_push_plane_effects(t_plane *plane)
{
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
	plane->diff_ratio.x = 100;
	plane->diff_ratio.y = 100;
	plane->cut_min.x = 0;
	plane->cut_min.y = 0;
	plane->cut_min.z = 0;
	plane->cut_max.x = 0;
	plane->cut_max.y = 0;
	plane->cut_max.z = 0;
	plane->u_axis = cross_vect(plane->normal);
}

void		xml_push_plane(t_env *e, t_node *list)
{
	t_plane plane;

	plane.size = sizeof(t_plane);
	plane.id = e->current_index_objects;
	plane.type = OBJ_PLANE;
	plane.flags = 0;
	plane.pos = list->pos;
	plane.normal = list->normale;
	plane.color = list->color;
	plane.diff = list->diff;
	plane.spec = list->spec;
	plane.reflex = list->reflex;
	plane.radius = list->radius;
	plane.refract = list->refract;
	plane.opacity = list->opacity;
	plane.limit_pos = list->limit_pos;
	plane.limit_dir = list->limit_dir;
	plane.flags = list->flags;
	xml_push_plane_effects(&plane);
	e->gen_objects->add(e->gen_objects, (void*)&plane);
}

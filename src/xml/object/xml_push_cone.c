/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_push_cone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 18:26:50 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/19 15:09:05 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_push_cone_effects(t_cone *cone)
{
	cone->waves_p1.x = 0.8;
	cone->waves_p1.y = 0.8;
	cone->waves_p1.z = 0.8;
	cone->waves_p2.x = 5;
	cone->waves_p2.y = 5;
	cone->waves_p2.z = 5;
	cone->check_size.x = 1;
	cone->check_size.y = 1;
	cone->diff_map_id = -1;
	cone->diff_offset.x = 0;
	cone->diff_offset.y = 0;
	cone->diff_ratio.x = 1;
	cone->diff_ratio.y = 1;
	cone->cut_min.x = 0;
	cone->cut_min.y = 0;
	cone->cut_min.z = 0;
	cone->cut_max.x = 0;
	cone->cut_max.y = 0;
	cone->cut_max.z = 0;
	cone->u_axis = cross_vect(cone->dir);
}

void		xml_push_cone(t_env *e, t_node *list)
{
	t_cone cone;

	cone.size = sizeof(t_cone);
	cone.id = e->current_index_objects;
	cone.type = OBJ_CONE;
	cone.flags = list->flags;
	cone.pos = list->pos;
	cone.angle = list->angle;
	cone.color = list->color;
	cone.diff = list->diff;
	cone.spec = list->spec;
	cone.reflex = list->reflex;
	cone.refract = list->refract;
	cone.opacity = list->opacity;
	cone.limit_pos = list->limit_pos;
	cone.limit_dir = list->limit_dir;
	cone.dir = normalize_vect(list->dir);
	xml_push_cone_effects(&cone);
	e->gen_objects->add(e->gen_objects, (void*)&cone);
}

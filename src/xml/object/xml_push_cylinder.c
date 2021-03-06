/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_push_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:56:46 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/22 17:45:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_push_cylinder_effects(t_cylinder *cylinder)
{
	cylinder->waves_p1.x = 0.8;
	cylinder->waves_p1.y = 0.8;
	cylinder->waves_p1.z = 0.8;
	cylinder->waves_p2.x = 5;
	cylinder->waves_p2.y = 5;
	cylinder->waves_p2.z = 5;
	cylinder->check_size.x = 1;
	cylinder->check_size.y = 1;
	cylinder->diff_map_id = -1;
	cylinder->diff_offset.x = 0;
	cylinder->diff_offset.y = 0;
	cylinder->diff_ratio.x = 1;
	cylinder->diff_ratio.y = 1;
	cylinder->u_axis = cross_vect(cylinder->dir);
	cylinder->cos.x = cosf(cylinder->dir.x);
	cylinder->cos.y = cosf(cylinder->dir.y);
	cylinder->cos.z = cosf(cylinder->dir.z);
	cylinder->sin.x = sinf(cylinder->dir.x);
	cylinder->sin.y = sinf(cylinder->dir.y);
	cylinder->sin.z = sinf(cylinder->dir.z);
}

void		xml_push_cyl(t_env *e, t_node *list)
{
	t_cylinder cylinder;

	cylinder.size = sizeof(t_cylinder);
	cylinder.id = e->current_index_objects;
	cylinder.type = OBJ_CYLINDER;
	cylinder.flags = list->flags;
	cylinder.pos = list->pos;
	cylinder.radius = list->radius;
	cylinder.color = list->color;
	cylinder.diff = list->diff;
	cylinder.spec = list->spec;
	cylinder.reflex = list->reflex;
	cylinder.refract = list->refract;
	cylinder.opacity = list->opacity;
	cylinder.limit_pos = list->limit_pos;
	cylinder.limit_dir = list->limit_dir;
	cylinder.dir = normalize_vect(list->dir);
	cylinder.cut_min = list->min;
	cylinder.cut_max = list->max;
	xml_push_cylinder_effects(&cylinder);
	e->gen_objects->add(e->gen_objects, (void*)&cylinder);
}

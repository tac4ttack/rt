/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_push_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 18:26:38 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/21 23:17:44 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_push_sphere_effects(t_sphere *sphere)
{
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

void		xml_push_sphere(t_env *e, t_node *list)
{
	t_sphere sphere;

	sphere.size = sizeof(t_sphere);
	sphere.id = e->current_index_objects;
	sphere.type = OBJ_SPHERE;
	sphere.pos = list->pos;
	sphere.flags = 0;
	sphere.dir = list->dir;
	sphere.radius = list->radius;
	sphere.color = list->color;
	sphere.diff = list->diff;
	sphere.spec = list->spec;
	sphere.reflex = list->reflex;
	sphere.refract = list->refract;
	sphere.opacity = list->opacity;
	sphere.limit_pos = list->limit_pos;
	sphere.limit_dir = list->limit_dir;
	sphere.flags = list->flags;
	sphere.cut_min = list->min;
	sphere.cut_max = list->max;
	xml_push_sphere_effects(&sphere);
	e->gen_objects->add(e->gen_objects, (void*)&sphere);
}

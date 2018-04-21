/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_push_kube.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 18:26:57 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/21 23:17:57 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	xml_push_kube_effects(t_kube *kube)
{
	kube->waves_p1.x = 0.8;
	kube->waves_p1.y = 0.8;
	kube->waves_p1.z = 0.8;
	kube->waves_p2.x = 5;
	kube->waves_p2.y = 5;
	kube->waves_p2.z = 5;
	kube->check_size.x = 1;
	kube->check_size.y = 1;
	kube->diff_map_id = -1;
	kube->diff_offset.x = 0;
	kube->diff_offset.y = 0;
	kube->diff_ratio.x = 1;
	kube->diff_ratio.y = 1;
}

void		xml_push_kube(t_env *e, t_node *list)
{
	t_kube kube;

	kube.size = sizeof(t_kube);
	kube.id = e->current_index_objects;
	kube.type = OBJ_KUBE;
	kube.pos = list->pos;
	kube.dir = list->dir;
	kube.option = list->radius;
	kube.color = list->color;
	kube.diff = list->diff;
	kube.spec = list->spec;
	kube.reflex = list->reflex;
	kube.refract = list->refract;
	kube.opacity = list->opacity;
	kube.limit_pos = list->limit_pos;
	kube.limit_dir = list->limit_dir;
	kube.flags = list->flags;
	kube.cut_min = list->min;
	kube.cut_max = list->max;
	xml_push_kube_effects(&kube);
	e->gen_objects->add(e->gen_objects, (void*)&kube);
}

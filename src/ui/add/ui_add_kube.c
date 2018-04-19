/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_add_kube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:59:37 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/19 15:09:05 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		ui_add_kube_effects(t_kube *kube)
{
	kube->limit_pos.x = 0;
	kube->limit_pos.y = 0;
	kube->limit_pos.z = 0;
	kube->limit_dir.x = 0;
	kube->limit_dir.y = 0;
	kube->limit_dir.z = 0;
	kube->waves_p1.x = 0.8;
	kube->waves_p1.y = 0.8;
	kube->waves_p1.z = 0.8;
	kube->waves_p2.x = 5;
	kube->waves_p2.y = 5;
	kube->waves_p2.z = 5;
	kube->check_size.x = 20;
	kube->check_size.y = 10;
	kube->diff_map_id = -1;
	kube->diff_offset.x = 0;
	kube->diff_offset.y = 0;
	kube->diff_ratio.x = 1;
	kube->diff_ratio.y = 1;
}

void			ui_add_kube(t_env *e)
{
	t_kube kube;

	kube.size = sizeof(t_kube);
	kube.id = e->gen_objects->length;
	kube.type = OBJ_KUBE;
	kube.pos.x = 0;
	kube.pos.y = 0;
	kube.pos.z = 0;
	kube.flags = 0;
	kube.dir = kube.pos;
	kube.dir.y = 1;
	kube.option = 11.8f;
	kube.color = rand();
	kube.diff.x = 0.42;
	kube.diff.y = 0.42;
	kube.diff.z = 0.42;
	kube.spec = kube.diff;
	kube.reflex = 0;
	kube.refract = 0;
	kube.opacity = 1;
	ui_add_kube_effects(&kube);
	e->gen_objects->add(e->gen_objects, (void*)&kube);
}

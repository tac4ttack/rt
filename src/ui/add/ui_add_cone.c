/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_add_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:59:59 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/02 17:34:43 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ui_add_cone(t_env *e)
{
	t_cone cone;

	cone.size = sizeof(t_cone);
	cone.type = OBJ_CONE;
	cone.id = e->gen_objects->length;
	cone.pos.x = 0;
	cone.pos.y = 0;
	cone.pos.z = 0;
	cone.flags = 0;
	cone.dir = cone.pos;
	cone.dir.z = 1;
	cone.angle = 4;
	cone.color = rand();
	cone.diff.x = 0.42;
	cone.diff.y = 0.42;
	cone.diff.z = 0.42;
	cone.spec = cone.diff;
	cone.reflex = 0;
	cone.refract = 0;
	cone.opacity = 1;
	e->gen_objects->add(e->gen_objects, (void*)&cone);
}

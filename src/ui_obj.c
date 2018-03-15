/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_obj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 15:03:16 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/15 19:49:11 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ui_obj(t_env *e, guint key)
{
	t_object	*obj;
	cl_float3	*target;

	obj = e->gen_objects->mem + e->target;
	target = NULL;
	if (key == GDK_KEY_I || key == GDK_KEY_J || key == GDK_KEY_K || key == GDK_KEY_L || key == GDK_KEY_U || key == GDK_KEY_O)
		target = &obj->dir;
	else
		target = &obj->pos;
	if (target)
	{
		(key == GDK_KEY_I ? *target = rotx(*target, 1 * DEG2RAD) : *target);
		(key == GDK_KEY_K ? *target = rotx(*target, -1 * DEG2RAD) : *target);
		(key == GDK_KEY_J ? *target = roty(*target, 1 * DEG2RAD) : *target);
		(key == GDK_KEY_L ? *target = roty(*target, -1 * DEG2RAD) : *target);
		(key == GDK_KEY_U ? *target = rotz(*target, 1 * DEG2RAD) : *target);
		(key == GDK_KEY_O ? *target = rotz(*target, -1 * DEG2RAD) : *target);
		(key == GDK_KEY_KP_4 ? target->x -= 0.1 : 0);
		(key == GDK_KEY_KP_6 ? target->x += 0.1 : 0);
		(key == GDK_KEY_KP_8 ? target->y -= 0.1 : 0);
		(key == GDK_KEY_KP_5 ? target->y += 0.1 : 0);
		(key == GDK_KEY_KP_7 ? target->z -= 0.1 : 0);
		(key == GDK_KEY_KP_9 ? target->z += 0.1 : 0);
	}
}


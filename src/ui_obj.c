/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_obj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 15:03:16 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/05 22:17:39 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ui_obj(t_env *e)
{
	t_object	*obj;
	cl_float3	*target;

	obj = e->gen_objects->mem + e->target;
	target = NULL;
	if (KP_I || KP_J || KP_K || KP_L || KP_U || KP_O)
		target = &obj->dir;
	else
		target = &obj->pos;
	if (target)
	{
		(KP_I ? *target = rotx(*target, 1 * DEG2RAD) : *target);
		(KP_K ? *target = rotx(*target, -1 * DEG2RAD) : *target);
		(KP_J ? *target = roty(*target, 1 * DEG2RAD) : *target);
		(KP_L ? *target = roty(*target, -1 * DEG2RAD) : *target);
		(KP_U ? *target = rotz(*target, 1 * DEG2RAD) : *target);
		(KP_O ? *target = rotz(*target, -1 * DEG2RAD) : *target);
		(KP_N4 ? target->x -= 0.1 : 0);
		(KP_N6 ? target->x += 0.1 : 0);
		(KP_N8 ? target->y -= 0.1 : 0);
		(KP_N5 ? target->y += 0.1 : 0);
		(KP_N7 ? target->z -= 0.1 : 0);
		(KP_N9 ? target->z += 0.1 : 0);
	}
}

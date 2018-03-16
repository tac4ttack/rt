/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_obj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 15:03:16 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/16 14:44:23 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ui_obj(t_env *e)
{
	t_object	*obj;
	cl_float3	*target;

	obj = e->gen_objects->mem + e->target;
	target = NULL;
	if (KEY_STATE_I || KEY_STATE_J || KEY_STATE_K || KEY_STATE_L || KEY_STATE_U || KEY_STATE_O)
		target = &obj->dir;
	else
		target = &obj->pos;
	if (target)
	{
		(KEY_STATE_I ? *target = rotx(*target, 1 * DEG2RAD) : *target);
		(KEY_STATE_K ? *target = rotx(*target, -1 * DEG2RAD) : *target);
		(KEY_STATE_J ? *target = roty(*target, 1 * DEG2RAD) : *target);
		(KEY_STATE_L ? *target = roty(*target, -1 * DEG2RAD) : *target);
		(KEY_STATE_U ? *target = rotz(*target, 1 * DEG2RAD) : *target);
		(KEY_STATE_O ? *target = rotz(*target, -1 * DEG2RAD) : *target);
		(KEY_STATE_N4 ? target->x -= 0.1 : 0);
		(KEY_STATE_N6 ? target->x += 0.1 : 0);
		(KEY_STATE_N8 ? target->y += 0.1 : 0);
		(KEY_STATE_N5 ? target->y -= 0.1 : 0);
		(KEY_STATE_N7 ? target->z -= 0.1 : 0);
		(KEY_STATE_N9 ? target->z += 0.1 : 0);
	}
	opencl_set_args(e, e->cl);
}


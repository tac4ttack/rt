/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_obj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 15:03:16 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/08 05:45:51 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ui_obj_apply(t_env *e, t_float3 *target)
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

void		ui_obj(t_env *e)
{
	t_object	*obj;
	t_float3	*target;

	if (e->target > -1)
	{
		obj = e->gen_objects->mem + e->target;
		target = NULL;
		if (KEY_STATE_I || KEY_STATE_J || KEY_STATE_K || KEY_STATE_L \
		|| KEY_STATE_U || KEY_STATE_O)
			target = &obj->dir;
		else
			target = &obj->pos;
		if (target)
			ui_obj_apply(e, target);
		if ((obj->type == OBJ_CYLINDER || obj->type == OBJ_CONE || \
		obj->type == OBJ_PLANE) && (KEY_STATE_I || KEY_STATE_J || \
		KEY_STATE_K || KEY_STATE_L || KEY_STATE_U || KEY_STATE_O))
		{
			if (obj->type == OBJ_CYLINDER)
				target = &((t_cylinder *)obj)->u_axis;
			else if (obj->type == OBJ_CONE)
				target = &((t_cone *)obj)->u_axis;
			else if (obj->type == OBJ_PLANE)
				target = &((t_plane *)obj)->u_axis;
			ui_obj_apply(e, target);
		}
		if (obj->flags & OBJ_FLAG_PLANE_LIMIT_FIX)
		{
			if (KEY_STATE_I || KEY_STATE_J || KEY_STATE_K || KEY_STATE_L \
			|| KEY_STATE_U || KEY_STATE_O)
				target = &obj->limit_dir;
			else
				target = &obj->limit_pos;
			if (target)
				ui_obj_apply(e, target);
		}
		ui_obj_update(e, obj);
	}
}

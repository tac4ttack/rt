/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_obj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 15:03:16 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/01 21:40:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
/*
cl_float3		*get_target_dir(t_env *e)
{
	cl_float3	*res;

	res = NULL;
	if (ACTIVEOBJ.type != 0)
	{
		if (ACTIVEOBJ.type == 1)
			res = &CONES[ACTIVEOBJ.id].dir;
		else if (ACTIVEOBJ.type == 2)
			res = &CYLIND[ACTIVEOBJ.id].dir;
		else if (ACTIVEOBJ.type == 4)
			res = &PLANE[ACTIVEOBJ.id].normale;
		else
			res = &SPHERE[ACTIVEOBJ.id].dir;
	}
	return (res);
}

cl_float3		*get_target_pos(t_env *e)
{
	cl_float3	*res;

	res = NULL;
	if (ACTIVEOBJ.type != 0)
	{
		if (ACTIVEOBJ.type == 1)
			res = &CONES[ACTIVEOBJ.id].pos;
		else if (ACTIVEOBJ.type == 2)
			res = &CYLIND[ACTIVEOBJ.id].pos;
		else if (ACTIVEOBJ.type == 4)
			res = &PLANE[ACTIVEOBJ.id].pos;
		else
			res = &SPHERE[ACTIVEOBJ.id].pos;
	}
	return (res);
}
*/
void			ui_obj(t_env *e)
{
	(void)e;
	return ;
	/*
	cl_float3	*target;

	target = NULL;
	if (KP_I || KP_J || KP_K || KP_L || KP_U || KP_O)
		target = get_target_dir(e);
	else
		target = get_target_pos(e);
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
	*/
}

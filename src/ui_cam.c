/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_cam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:02:45 by adalenco          #+#    #+#             */
/*   Updated: 2018/02/26 19:02:47 by adalenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		rot_cam(t_env *e)
{
	if (KP_W)
		ACTIVECAM.pos = add_cl_float(rotcam(ACTIVECAM.dir, \
		ACTIVECAM.pitch * DEG2RAD, ACTIVECAM.yaw * DEG2RAD), ACTIVECAM.pos);
	if (KP_S)
		ACTIVECAM.pos = sub_cl_float(ACTIVECAM.pos, rotcam(ACTIVECAM.dir, \
		ACTIVECAM.pitch * DEG2RAD, ACTIVECAM.yaw * DEG2RAD));
	if (KP_C)
		ACTIVECAM.pos = add_cl_float(rotcam(ACTIVECAM.dir, (ACTIVECAM.pitch + \
		90) * DEG2RAD, ACTIVECAM.yaw * DEG2RAD), ACTIVECAM.pos);
	if (KP_SPC)
		ACTIVECAM.pos = add_cl_float(rotcam(ACTIVECAM.dir, (ACTIVECAM.pitch - \
		90) * DEG2RAD, ACTIVECAM.yaw * DEG2RAD), ACTIVECAM.pos);
	if (KP_D)
		ACTIVECAM.pos = add_cl_float(rotcam(ACTIVECAM.dir, 0, (ACTIVECAM.yaw + \
		90) * DEG2RAD), ACTIVECAM.pos);
	if (KP_A)
		ACTIVECAM.pos = add_cl_float(rotcam(ACTIVECAM.dir, 0, (ACTIVECAM.yaw - \
		90) * DEG2RAD), ACTIVECAM.pos);
}

void		ui_cam(t_env *e)
{
	if (KP_W || KP_S || KP_C || KP_SPC || KP_D || KP_A)
		rot_cam(e);
	(KP_DA ? ACTIVECAM.pitch += 2 : 0);
	(KP_UA ? ACTIVECAM.pitch -= 2 : 0);
	(KP_LA ? ACTIVECAM.yaw -= 2 : 0);
	(KP_RA ? ACTIVECAM.yaw += 2 : 0);
	(ACTIVECAM.pitch >= 360 ? ACTIVECAM.pitch = 0 : ACTIVECAM.pitch);
	(ACTIVECAM.pitch < 0 ? ACTIVECAM.pitch = 359 : ACTIVECAM.pitch);
	(ACTIVECAM.yaw >= 360 ? ACTIVECAM.yaw = 0 : ACTIVECAM.yaw);
	(ACTIVECAM.yaw < 0 ? ACTIVECAM.yaw = 359 : ACTIVECAM.yaw);
	(ACTIVECAM.roll >= 360 ? ACTIVECAM.roll = 0 : ACTIVECAM.roll);
	(ACTIVECAM.roll < 0 ? ACTIVECAM.roll = 359 : ACTIVECAM.roll);
	if (KP_Z)
		e->scene->active_cam = (e->scene->active_cam + 1 \
		< e->scene->n_cams ? e->scene->active_cam + 1 : 0);
}

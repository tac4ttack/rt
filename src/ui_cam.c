/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_cam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:02:45 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/15 19:57:36 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		rot_cam(t_env *e, guint key)
{
	if (key == GDK_KEY_W)
		ACTIVECAM.pos = add_cl_float(rotcam(ACTIVECAM.dir, \
		ACTIVECAM.pitch * DEG2RAD, ACTIVECAM.yaw * DEG2RAD), ACTIVECAM.pos);
	if (key == GDK_KEY_S)
		ACTIVECAM.pos = sub_cl_float(ACTIVECAM.pos, rotcam(ACTIVECAM.dir, \
		ACTIVECAM.pitch * DEG2RAD, ACTIVECAM.yaw * DEG2RAD));
	if (key == GDK_KEY_C)
		ACTIVECAM.pos = add_cl_float(rotcam(ACTIVECAM.dir, (ACTIVECAM.pitch + \
		90) * DEG2RAD, ACTIVECAM.yaw * DEG2RAD), ACTIVECAM.pos);
	if (key == GDK_KEY_space)
		ACTIVECAM.pos = add_cl_float(rotcam(ACTIVECAM.dir, (ACTIVECAM.pitch - \
		90) * DEG2RAD, ACTIVECAM.yaw * DEG2RAD), ACTIVECAM.pos);
	if (key == GDK_KEY_D)
		ACTIVECAM.pos = add_cl_float(rotcam(ACTIVECAM.dir, 0, (ACTIVECAM.yaw + \
		90) * DEG2RAD), ACTIVECAM.pos);
	if (key == GDK_KEY_A)
		ACTIVECAM.pos = add_cl_float(rotcam(ACTIVECAM.dir, 0, (ACTIVECAM.yaw - \
		90) * DEG2RAD), ACTIVECAM.pos);
}

void		ui_cam(t_env *e, guint key)
{
	ft_putendl("im in uicam");
	if (key == GDK_KEY_W || key == GDK_KEY_S || key == GDK_KEY_C || key == GDK_KEY_space || key == GDK_KEY_D || key == GDK_KEY_A)
		rot_cam(e, key);
	(key == GDK_KEY_downarrow ? ACTIVECAM.pitch += 2 : 0);
	(key == 65362 ? ACTIVECAM.pitch -= 2 : 0);
	(key == GDK_KEY_leftarrow ? ACTIVECAM.yaw -= 2 : 0);
	(key == GDK_KEY_rightarrow ? ACTIVECAM.yaw += 2 : 0);
	(ACTIVECAM.pitch >= 360 ? ACTIVECAM.pitch = 0 : ACTIVECAM.pitch);
	(ACTIVECAM.pitch < 0 ? ACTIVECAM.pitch = 359 : ACTIVECAM.pitch);
	(ACTIVECAM.yaw >= 360 ? ACTIVECAM.yaw = 0 : ACTIVECAM.yaw);
	(ACTIVECAM.yaw < 0 ? ACTIVECAM.yaw = 359 : ACTIVECAM.yaw);
	(ACTIVECAM.roll >= 360 ? ACTIVECAM.roll = 0 : ACTIVECAM.roll);
	(ACTIVECAM.roll < 0 ? ACTIVECAM.roll = 359 : ACTIVECAM.roll);
	if (key == GDK_KEY_Z)
		e->scene->active_cam = (e->scene->active_cam + 1 \
		< e->scene->n_cams ? e->scene->active_cam + 1 : 0);
}


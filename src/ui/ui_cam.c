/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_cam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:02:45 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/30 20:08:18 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		rot_cam(t_env *e)
{
	if (KEY_STATE_W)
		ACTIVECAM.pos = add_cl_float(rotcam(ACTIVECAM.dir, \
		ACTIVECAM.pitch * DEG2RAD, ACTIVECAM.yaw * DEG2RAD), ACTIVECAM.pos);
	if (KEY_STATE_S)
		ACTIVECAM.pos = sub_cl_float(ACTIVECAM.pos, rotcam(ACTIVECAM.dir, \
		ACTIVECAM.pitch * DEG2RAD, ACTIVECAM.yaw * DEG2RAD));
	if (KEY_STATE_C)
		ACTIVECAM.pos = add_cl_float(rotcam(ACTIVECAM.dir, (ACTIVECAM.pitch + \
		90) * DEG2RAD, ACTIVECAM.yaw * DEG2RAD), ACTIVECAM.pos);
	if (KEY_STATE_SPC)
		ACTIVECAM.pos = add_cl_float(rotcam(ACTIVECAM.dir, (ACTIVECAM.pitch - \
		90) * DEG2RAD, ACTIVECAM.yaw * DEG2RAD), ACTIVECAM.pos);
	if (KEY_STATE_D)
		ACTIVECAM.pos = add_cl_float(rotcam(ACTIVECAM.dir, 0, (ACTIVECAM.yaw + \
		90) * DEG2RAD), ACTIVECAM.pos);
	if (KEY_STATE_A)
		ACTIVECAM.pos = add_cl_float(rotcam(ACTIVECAM.dir, 0, (ACTIVECAM.yaw - \
		90) * DEG2RAD), ACTIVECAM.pos);
}

void		ui_cam(t_env *e)
{
	char	*cam_id;

	if (KEY_STATE_W || KEY_STATE_S || KEY_STATE_C || KEY_STATE_SPC\
									|| KEY_STATE_D || KEY_STATE_A)
		rot_cam(e);
	(KEY_STATE_DA ? ACTIVECAM.pitch += 2 : 0);
	(KEY_STATE_UA ? ACTIVECAM.pitch -= 2 : 0);
	(KEY_STATE_LA ? ACTIVECAM.yaw -= 2 : 0);
	(KEY_STATE_RA ? ACTIVECAM.yaw += 2 : 0);
	(ACTIVECAM.pitch >= 360 ? ACTIVECAM.pitch = 0 : ACTIVECAM.pitch);
	(ACTIVECAM.pitch < 0 ? ACTIVECAM.pitch = 359 : ACTIVECAM.pitch);
	(ACTIVECAM.yaw >= 360 ? ACTIVECAM.yaw = 0 : ACTIVECAM.yaw);
	(ACTIVECAM.yaw < 0 ? ACTIVECAM.yaw = 359 : ACTIVECAM.yaw);
	(ACTIVECAM.roll >= 360 ? ACTIVECAM.roll = 0 : ACTIVECAM.roll);
	(ACTIVECAM.roll < 0 ? ACTIVECAM.roll = 359 : ACTIVECAM.roll);
	if (KEY_STATE_Z)
	{
		e->scene->active_cam = (e->scene->active_cam + 1 \
		< e->scene->n_cams ? e->scene->active_cam + 1 : 0);
		cam_id = ft_strjoin_frs2("CAMERA #", ft_itoa(e->scene->active_cam + 1));
		gtk_label_set_text(GTK_LABEL(e->ui->cam_list_id_label), (gchar*)cam_id);
		free(cam_id);
	}
	ui_cam_update(e);
	opencl_set_args(e, e->cl);
}

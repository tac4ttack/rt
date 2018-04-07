/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_cam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:02:45 by adalenco          #+#    #+#             */
/*   Updated: 2018/04/07 16:38:58 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		rot_cam(t_env *e)
{
	if (KEY_STATE_W)
		A_CAM.pos = add_cl_float(rotcam(A_CAM.dir, \
		A_CAM.pitch * DEG2RAD, A_CAM.yaw * DEG2RAD), A_CAM.pos);
	if (KEY_STATE_S)
		A_CAM.pos = sub_cl_float(A_CAM.pos, rotcam(A_CAM.dir, \
		A_CAM.pitch * DEG2RAD, A_CAM.yaw * DEG2RAD));
	if (KEY_STATE_C)
		A_CAM.pos = add_cl_float(rotcam(A_CAM.dir, (A_CAM.pitch + \
		90) * DEG2RAD, A_CAM.yaw * DEG2RAD), A_CAM.pos);
	if (KEY_STATE_SPC)
		A_CAM.pos = add_cl_float(rotcam(A_CAM.dir, (A_CAM.pitch - \
		90) * DEG2RAD, A_CAM.yaw * DEG2RAD), A_CAM.pos);
	if (KEY_STATE_D)
		A_CAM.pos = add_cl_float(rotcam(A_CAM.dir, 0, (A_CAM.yaw + \
		90) * DEG2RAD), A_CAM.pos);
	if (KEY_STATE_A)
		A_CAM.pos = add_cl_float(rotcam(A_CAM.dir, 0, (A_CAM.yaw - \
		90) * DEG2RAD), A_CAM.pos);
}

void		ui_cam(t_env *e)
{
	char	*cam_id;

	if (KEY_STATE_W || KEY_STATE_S || KEY_STATE_C || KEY_STATE_SPC\
									|| KEY_STATE_D || KEY_STATE_A)
		rot_cam(e);
	(KEY_STATE_DA ? A_CAM.pitch += 2 : 0);
	(KEY_STATE_UA ? A_CAM.pitch -= 2 : 0);
	(KEY_STATE_LA ? A_CAM.yaw -= 2 : 0);
	(KEY_STATE_RA ? A_CAM.yaw += 2 : 0);
	(A_CAM.pitch >= 360 ? A_CAM.pitch = 0 : A_CAM.pitch);
	(A_CAM.pitch < 0 ? A_CAM.pitch = 359 : A_CAM.pitch);
	(A_CAM.yaw >= 360 ? A_CAM.yaw = 0 : A_CAM.yaw);
	(A_CAM.yaw < 0 ? A_CAM.yaw = 359 : A_CAM.yaw);
	(A_CAM.roll >= 360 ? A_CAM.roll = 0 : A_CAM.roll);
	(A_CAM.roll < 0 ? A_CAM.roll = 359 : A_CAM.roll);
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

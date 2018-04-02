/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_cam_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:04:47 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/02 12:11:24 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ui_cam_update(t_env *e)
{
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_pos_spin_x, \
	(gdouble)A_CAM.pos.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_pos_spin_y, \
	(gdouble)A_CAM.pos.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_pos_spin_z, \
	(gdouble)A_CAM.pos.z);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_dir_spin_x, \
	(gdouble)A_CAM.pitch);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_dir_spin_y, \
	(gdouble)A_CAM.yaw);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_dir_spin_z, \
	(gdouble)A_CAM.roll);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_fov_spin, \
	(gint)A_CAM.fov);
}

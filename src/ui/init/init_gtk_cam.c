/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gtk_cam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:00:34 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/01 12:02:51 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_gtk_cam_adds(t_env *e)
{
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_dir_spin_y, \
	(gdouble)A_CAM.dir.y);
	e->ui->cam_list_dir_spin_z = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "cam_list_dir_spin_z"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_dir_spin_z, \
	(gdouble)A_CAM.dir.z);
	e->ui->cam_list_fov_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "cam_list_fov_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_fov_spin, \
	(guint)A_CAM.fov);
	e->ui->cam_nav_prev_btn = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "cam_nav_prev_btn"));
	e->ui->cam_nav_next_btn = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "cam_nav_next_btn"));
	e->ui->cam_nav_add_btn = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "cam_nav_add_btn"));
	e->ui->cam_nav_del_btn = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "cam_nav_del_btn"));
	if (e->scene->n_cams < 2)
	{
		gtk_widget_set_sensitive(e->ui->cam_nav_prev_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->cam_nav_next_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->cam_nav_del_btn, FALSE);
	}
}

void		init_gtk_cam(t_env *e)
{
	e->ui->cam_list_id_label = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "cam_list_id_label"));
	ui_cam_set_id(e);
	e->ui->cam_list_pos_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "cam_list_pos_spin_x"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_pos_spin_x, \
	(gdouble)A_CAM.pos.x);
	e->ui->cam_list_pos_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "cam_list_pos_spin_y"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_pos_spin_y, \
	(gdouble)A_CAM.pos.y);
	e->ui->cam_list_pos_spin_z = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "cam_list_pos_spin_z"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_pos_spin_z, \
	(gdouble)A_CAM.pos.z);
	e->ui->cam_list_dir_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "cam_list_dir_spin_x"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_dir_spin_x, \
	(gdouble)A_CAM.dir.x);
	e->ui->cam_list_dir_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "cam_list_dir_spin_y"));
	init_gtk_cam_adds(e);
}

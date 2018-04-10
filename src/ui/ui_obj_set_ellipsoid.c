/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_obj_set_ellipsoid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:11:16 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/10 19:41:16 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	show_only_ellipsoid(t_env *e)
{
	gtk_widget_hide(e->ui->obj_list_cone);
	gtk_widget_hide(e->ui->obj_list_cylinder);
	gtk_widget_show(e->ui->obj_list_ellipsoid);
	gtk_widget_hide(e->ui->obj_list_plane);
	gtk_widget_hide(e->ui->obj_list_sphere);
	gtk_widget_hide(e->ui->obj_list_torus);
	gtk_widget_hide(e->ui->obj_list_checkboard);
	gtk_widget_show(e->ui->obj_list_limit);
	gtk_widget_show(e->ui->obj_list_sinwave);
	gtk_widget_hide(e->ui->obj_list_texture_diff);
	gtk_widget_hide(e->ui->obj_cut_check); // WIP
}

void		ui_obj_set_ellipsoid(t_env *e, t_ellipsoid *obj)
{
	show_only_ellipsoid(e);
	ui_obj_update_checkboard(e, (t_object *)obj);
	ui_obj_update_diff_map(e, (t_object *)obj);
	ui_obj_update_limit(e, (t_object *)obj);
	ui_obj_update_sinwave(e, (t_object *)obj);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_ellipsoid_radius_spin,\
	(gdouble)obj->radius);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_ellipsoid_axis_spin_x,\
	(gdouble)obj->axis_size.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_ellipsoid_axis_spin_y,\
	(gdouble)obj->axis_size.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_ellipsoid_axis_spin_z,\
	(gdouble)obj->axis_size.z);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_obj_set_ellipsoid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:11:16 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:11:43 by fmessina         ###   ########.fr       */
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
}

void		ui_obj_set_ellipsoid(t_env *e, t_ellipsoid *obj)
{
	show_only_ellipsoid(e);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_ellipsoid_radius_spin,\
	(gdouble)obj->radius);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_ellipsoid_axis_spin_x,\
	(gdouble)obj->axis_size.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_ellipsoid_axis_spin_y,\
	(gdouble)obj->axis_size.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_ellipsoid_axis_spin_z,\
	(gdouble)obj->axis_size.z);
}
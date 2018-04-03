/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_obj_set_cone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:10:36 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 18:01:00 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	show_only_cone(t_env *e)
{
	gtk_widget_show(e->ui->obj_list_cone);
	gtk_widget_hide(e->ui->obj_list_cylinder);
	gtk_widget_hide(e->ui->obj_list_ellipsoid);
	gtk_widget_hide(e->ui->obj_list_plane);
	gtk_widget_hide(e->ui->obj_list_sphere);
	gtk_widget_hide(e->ui->obj_list_torus);
	gtk_widget_hide(e->ui->obj_list_checkboard);
	gtk_widget_show(e->ui->obj_list_limit);
	gtk_widget_show(e->ui->obj_list_sinwave);
	gtk_widget_show(e->ui->obj_list_texture_diff);
}

void		ui_obj_set_cone(t_env *e, t_cone *obj)
{
	show_only_cone(e);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_cone_angle_spin, \
	(gdouble)obj->angle);
}

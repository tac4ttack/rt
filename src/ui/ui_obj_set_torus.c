/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_obj_set_torus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:12:20 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:12:25 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	show_only_torus(t_env *e)
{
	gtk_widget_hide(e->ui->obj_list_cone);
	gtk_widget_hide(e->ui->obj_list_cylinder);
	gtk_widget_hide(e->ui->obj_list_ellipsoid);
	gtk_widget_hide(e->ui->obj_list_plane);
	gtk_widget_hide(e->ui->obj_list_sphere);
	gtk_widget_show(e->ui->obj_list_torus);
}

void		ui_obj_set_torus(t_env *e, t_torus *obj)
{
	show_only_torus(e);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_torus_lilradius_spin, \
	(gdouble)obj->lil_radius);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_torus_bigradius_spin, \
	(gdouble)obj->big_radius);
}

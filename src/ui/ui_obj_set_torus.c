/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_obj_set_torus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:12:20 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/10 19:48:49 by fmessina         ###   ########.fr       */
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
	gtk_widget_hide(e->ui->obj_list_checkboard);
	gtk_widget_hide(e->ui->obj_list_limit);
	gtk_widget_show(e->ui->obj_list_sinwave);
	gtk_widget_hide(e->ui->obj_list_texture_diff);
	gtk_widget_hide(e->ui->obj_list_cut);
}

void		ui_obj_set_torus(t_env *e, t_torus *obj)
{
	show_only_torus(e);
	ui_obj_update_checkboard(e, (t_object *)obj);
	ui_obj_update_diff_map(e, (t_object *)obj);
	ui_obj_update_limit(e, (t_object *)obj);
	ui_obj_update_sinwave(e, (t_object *)obj);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_torus_lilradius_spin, \
	(gdouble)obj->lil_radius);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_torus_bigradius_spin, \
	(gdouble)obj->big_radius);
}

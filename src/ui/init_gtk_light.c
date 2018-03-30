/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gtk_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:00:30 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:00:30 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_gtk_light_adds(t_env *e)
{
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_shrink_spin, \
	(gint)ACTIVELIGHT.shrink);
	e->ui->light_list_color_btn = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "light_list_color_btn"));
	e->ui->light_color = int_to_gdkrbga((gint)ACTIVELIGHT.color);
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(e->ui->light_list_color_btn), \
	&e->ui->light_color);
	e->ui->light_nav_prev_btn = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "light_nav_prev_btn"));
	e->ui->light_nav_next_btn = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "light_nav_next_btn"));
	e->ui->light_nav_add_btn = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "light_nav_add_btn"));
	e->ui->light_nav_del_btn = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "light_nav_del_btn"));
	if (e->gen_lights->length < 2)
	{
		gtk_widget_set_sensitive(e->ui->light_nav_prev_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->light_nav_next_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->light_nav_del_btn, FALSE);
	}
}

void		init_gtk_light(t_env *e)
{
	e->ui->light_list_id_label = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "light_list_id_label"));
	ui_light_set_id(e);
	e->ui->light_list_pos_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "light_list_pos_spin_x"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_pos_spin_x, \
	(gdouble)ACTIVELIGHT.pos.x);
	e->ui->light_list_pos_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "light_list_pos_spin_y"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_pos_spin_y, \
	(gdouble)ACTIVELIGHT.pos.y);
	e->ui->light_list_pos_spin_z = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "light_list_pos_spin_z"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_pos_spin_z, \
	(gdouble)ACTIVELIGHT.pos.z);
	e->ui->light_list_bright_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "light_list_bright_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_bright_spin, \
	(gdouble)ACTIVELIGHT.brightness);
	e->ui->light_list_shrink_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "light_list_shrink_spin"));
	init_gtk_light_adds(e);
}

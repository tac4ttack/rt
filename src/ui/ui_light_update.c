/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_light_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:08:48 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/01 12:03:18 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ui_light_update(t_env *e)
{
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_pos_spin_x, \
	(gdouble)A_LIG.pos.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_pos_spin_y, \
	(gdouble)A_LIG.pos.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_pos_spin_z, \
	(gdouble)A_LIG.pos.z);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_bright_spin, \
	(gdouble)A_LIG.brightness);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_shrink_spin, \
	(gint)A_LIG.shrink);
	e->ui->light_color = int_to_gdkrbga((gint)A_LIG.color);
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(e->ui-> light_list_color_btn),\
	&e->ui->light_color);
}

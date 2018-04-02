/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cam_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:44 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/01 12:02:51 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean		cb_cam_pos_x(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;

	e = data;
	value = gtk_spin_button_get_value(spin);
	A_CAM.pos.x = (float)value;
	return (TRUE);
}

gboolean		cb_cam_pos_y(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;

	e = data;
	value = gtk_spin_button_get_value(spin);
	A_CAM.pos.y = (float)value;
	return (TRUE);
}

gboolean		cb_cam_pos_z(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;

	e = data;
	value = gtk_spin_button_get_value(spin);
	A_CAM.pos.z = (float)value;
	return (TRUE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cam_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:44 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/05 23:25:44 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean		cb_cam_dir_x(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	value = gtk_spin_button_get_value(spin);
	A_CAM.pitch = (float)value;
	return (TRUE);
}

gboolean		cb_cam_dir_y(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	value = gtk_spin_button_get_value(spin);
	A_CAM.yaw = (float)value;
	return (TRUE);
}

gboolean		cb_cam_dir_z(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	value = gtk_spin_button_get_value(spin);
	A_CAM.roll = (float)value;
	return (TRUE);
}

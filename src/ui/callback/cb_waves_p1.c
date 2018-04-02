/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_waves_p1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:07 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/01 18:24:53 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean		cb_waves_p1_x(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;

	e = data;
	value = gtk_spin_button_get_value(spin);
	e->scene->waves_p1.x = (float)value;
	return (TRUE);
}

gboolean		cb_waves_p1_y(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;

	e = data;
	value = gtk_spin_button_get_value(spin);
	e->scene->waves_p1.y = (float)value;
	return (TRUE);
}

gboolean		cb_waves_p1_z(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;

	e = data;
	value = gtk_spin_button_get_value(spin);
	e->scene->waves_p1.z = (float)value;
	return (TRUE);
}

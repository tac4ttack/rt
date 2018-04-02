/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_ellipsoid_axis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:56 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:48:20 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean		cb_ellipsoid_axis_x(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_ellipsoid	*ellipsoid;

	e = data;
	ellipsoid = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	ellipsoid->axis_size.x = (float)value;
	return (TRUE);
}

gboolean		cb_ellipsoid_axis_y(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_ellipsoid	*ellipsoid;

	e = data;
	ellipsoid = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	ellipsoid->axis_size.y = (float)value;
	return (TRUE);
}

gboolean		cb_ellipsoid_axis_z(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_ellipsoid	*ellipsoid;

	e = data;
	ellipsoid = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	ellipsoid->axis_size.z = (float)value;
	return (TRUE);
}

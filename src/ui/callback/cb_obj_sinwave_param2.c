/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_sinwave_param2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 15:47:45 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 16:03:36 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean		cb_obj_sinwave_param2_x(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	obj->waves_p2.x = (float)value;
	return (TRUE);
}

gboolean		cb_obj_sinwave_param2_y(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	obj->waves_p2.y = (float)value;
	return (TRUE);
}

gboolean		cb_obj_sinwave_param2_z(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	obj->waves_p2.z = (float)value;
	return (TRUE);
}

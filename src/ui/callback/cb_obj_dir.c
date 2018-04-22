/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:13 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/22 17:42:35 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean		cb_obj_dir_x(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	obj->dir.x = (float)value;
	if (obj->dir.x == 0.0f && obj->dir.y == 0.0f && obj->dir.z == 0.0f)
		obj->dir.x = 0.1;
	if (obj->type == OBJ_CYLINDER)
		((t_cylinder*)obj)->u_axis = cross_vect(obj->dir);
	else if (obj->type == OBJ_CONE)
		((t_cone*)obj)->u_axis = cross_vect(obj->dir);
	else if (obj->type == OBJ_PLANE)
		((t_plane*)obj)->u_axis = cross_vect(obj->dir);
	obj->dir = normalize_vect(obj->dir);
	obj->cos.x = cosf(obj->dir.x);
	obj->sin.x = sinf(obj->dir.x);
	return (TRUE);
}

gboolean		cb_obj_dir_y(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	obj->dir.y = (float)value;
	if (obj->dir.x == 0.0f && obj->dir.y == 0.0f && obj->dir.z == 0.0f)
		obj->dir.y = 0.1;
	if (obj->type == OBJ_CYLINDER)
		((t_cylinder*)obj)->u_axis = cross_vect(obj->dir);
	else if (obj->type == OBJ_CONE)
		((t_cone*)obj)->u_axis = cross_vect(obj->dir);
	else if (obj->type == OBJ_PLANE)
		((t_plane*)obj)->u_axis = cross_vect(obj->dir);
	obj->dir = normalize_vect(obj->dir);
	obj->cos.y = cosf(obj->dir.y);
	obj->sin.y = sinf(obj->dir.y);
	return (TRUE);
}

gboolean		cb_obj_dir_z(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	obj->dir.z = (float)value;
	if (obj->dir.x == 0.0f && obj->dir.y == 0.0f && obj->dir.z == 0.0f)
		obj->dir.z = 0.1;
	if (obj->type == OBJ_CYLINDER)
		((t_cylinder*)obj)->u_axis = cross_vect(obj->dir);
	else if (obj->type == OBJ_CONE)
		((t_cone*)obj)->u_axis = cross_vect(obj->dir);
	else if (obj->type == OBJ_PLANE)
		((t_plane*)obj)->u_axis = cross_vect(obj->dir);
	obj->dir = normalize_vect(obj->dir);
	obj->cos.z = cosf(obj->dir.z);
	obj->sin.z = sinf(obj->dir.z);
	return (TRUE);
}

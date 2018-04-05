/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:13 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:44:30 by fmessina         ###   ########.fr       */
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
	if (obj->type == OBJ_CYLINDER)
	{
		((t_cylinder *)obj)->u_axis.z = obj->dir.x;
		((t_cylinder *)obj)->u_axis = normalize_vect(((t_cylinder *)obj)->u_axis);
	}
	else if (obj->type == OBJ_CONE)
	{
		((t_cone *)obj)->u_axis.z = obj->dir.x;
		((t_cone *)obj)->u_axis = normalize_vect(((t_cone*)obj)->u_axis);
	}
	else if (obj->type == OBJ_PLANE)
	{
		((t_plane *)obj)->u_axis.z = obj->dir.x;
		((t_plane *)obj)->u_axis = normalize_vect(((t_plane *)obj)->u_axis);
	}
	obj->dir = normalize_vect(obj->dir);
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
	if (obj->type == OBJ_CYLINDER)
	{
		((t_cylinder *)obj)->u_axis.x = obj->dir.y;
		((t_cylinder *)obj)->u_axis = normalize_vect(((t_cylinder *)obj)->u_axis);
	}
	else if (obj->type == OBJ_CONE)
	{
		((t_cone *)obj)->u_axis.x = obj->dir.y;
		((t_cone *)obj)->u_axis = normalize_vect(((t_cone *)obj)->u_axis);
	}
	else if (obj->type == OBJ_PLANE)
	{
		((t_plane *)obj)->u_axis.x = obj->dir.y;
		((t_plane *)obj)->u_axis = normalize_vect(((t_plane *)obj)->u_axis);
	}
	obj->dir = normalize_vect(obj->dir);
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
	if (obj->type == OBJ_CYLINDER)
	{
		((t_cylinder *)obj)->u_axis.y = obj->dir.z;
		((t_cylinder *)obj)->u_axis = normalize_vect(((t_cylinder *)obj)->u_axis);
	}
	else if (obj->type == OBJ_CONE)
	{
		((t_cone *)obj)->u_axis.y = obj->dir.z;
		((t_cone *)obj)->u_axis = normalize_vect(((t_cone *)obj)->u_axis);
	}
	else if (obj->type == OBJ_PLANE)
	{
		((t_plane *)obj)->u_axis.y = obj->dir.z;
		((t_plane *)obj)->u_axis = normalize_vect(((t_plane *)obj)->u_axis);
	}
	obj->dir = normalize_vect(obj->dir);
	return (TRUE);
}

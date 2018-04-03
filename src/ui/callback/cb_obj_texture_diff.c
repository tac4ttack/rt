/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_texture_diff.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 15:47:45 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 16:10:00 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			cb_obj_texture_diff_button(GtkButton *btn, gpointer data)
{
	t_env		*e;
	t_object	*obj;

	(void)btn;
	e = data;
	obj = e->gen_objects->mem + e->target;
	if (obj->flags & OBJ_FLAG_DIFF_MAP)
		obj->flags ^= OBJ_FLAG_DIFF_MAP;
	else
		obj->flags |= OBJ_FLAG_DIFF_MAP;
}

gboolean		cb_obj_texture_diff_offset_x(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	obj->diff_map_size.x = (float)value;
	return (TRUE);
}

gboolean		cb_obj_texture_diff_offset_y(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	obj->diff_map_size.y = (float)value;
	return (TRUE);
}

gboolean		cb_obj_texture_diff_ratio(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	obj->diff_map_size.z = (float)value;
	return (TRUE);
}

void		cb_obj_texture_diff_chooser(GtkComboBox *box, gpointer data)
{
	t_env	*e;
//	gint	index;
	//void	*obj;

	e = data;
	(void)box;
	ft_putendl("TOTO CACA!");
	// index = gtk_combo_box_get_active(box);
	// if (index > -1)
	// {
	// 	obj = gen_get_index_ptr(e->gen_objects, index);
	// 	e->target = obj - e->gen_objects->mem;
	// 	ui_obj_update(e, obj);
	// }
}

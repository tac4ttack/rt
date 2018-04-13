/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_nav_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:19 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/08 01:37:04 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_object	*obj_nav_create_obj(t_env *e, int t)
{
	t_object	*obj;

	if (t == 0)
		ui_add_cone(e);
	else if (t == 1)
		ui_add_cylinder(e);
	else if (t == 2)
		ui_add_ellipsoid(e);
	else if (t == 3)
		ui_add_plane(e);
	else if (t == 4)
		ui_add_sphere(e);
	else if (t == 5)
		ui_add_torus(e);
	obj = (t_object*)gen_get_index_ptr(e->gen_objects, \
										e->gen_objects->length - 1);
	e->target = (void*)obj - e->gen_objects->mem;
	return (obj);
}

void			cb_obj_nav_add(GtkButton *btn, gpointer data)
{
	t_env		*e;
	gint		t;
	t_object	*obj;

	(void)btn;
	e = data;
	t = gtk_combo_box_get_active((GtkComboBox*)e->ui->obj_nav_add_type_combo);
	obj = obj_nav_create_obj(e, t);
	//if (!(cl_replace_buffer(e->cl, e->gen_objects->mem_size, 1)))
	//	s_error("\x1b[2;31mFailed replacing cam buffer\x1b[0m", e);
	gtk_widget_set_sensitive(e->ui->obj_nav_prev_btn, TRUE);
	gtk_widget_set_sensitive(e->ui->obj_nav_next_btn, TRUE);
	gtk_widget_set_sensitive(e->ui->obj_nav_del_btn, TRUE);
	ui_obj_update(e, obj);
	ui_obj_jump_list(e);
}

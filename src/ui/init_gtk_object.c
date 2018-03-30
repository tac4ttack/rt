/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gtk_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:00:25 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:00:28 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_gtk_object_first_adds(t_env *e)
{
	e->ui->obj_list_diff_spin_z = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_diff_spin_z"));
	e->ui->obj_list_spec_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_spec_spin_x"));
	e->ui->obj_list_spec_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_spec_spin_y"));
	e->ui->obj_list_spec_spin_z = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_spec_spin_z"));
	e->ui->obj_list_reflex_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_reflex_spin"));
	e->ui->obj_list_refrac_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_refrac_spin"));
	e->ui->obj_list_opacity_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_opacity_spin"));
	e->ui->obj_list_color_btn = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_color_btn"));
	e->ui->obj_list_cone = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_cone"));
	e->ui->obj_cone_angle_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_cone_angle_spin"));
	e->ui->obj_list_cylinder = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_cylinder"));
	e->ui->obj_cylinder_radius_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_cylinder_radius_spin"));
}

static void	init_gtk_object_second_adds(t_env *e)
{
	e->ui->obj_cylinder_height_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_cylinder_height_spin"));
	e->ui->obj_list_ellipsoid = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_ellipsoid"));
	e->ui->obj_ellipsoid_axis_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_ellipsoid_axis_spin_x"));
	e->ui->obj_ellipsoid_axis_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_ellipsoid_axis_spin_y"));
	e->ui->obj_ellipsoid_axis_spin_z = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_ellipsoid_axis_spin_z"));
	e->ui->obj_ellipsoid_radius_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_ellipsoid_radius_spin"));
	e->ui->obj_list_plane = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_plane"));
	e->ui->obj_list_sphere = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_sphere"));
	e->ui->obj_sphere_radius_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_sphere_radius_spin"));
	e->ui->obj_list_torus = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_torus"));
	e->ui->obj_torus_lilradius_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_torus_lilradius_spin"));
	e->ui->obj_torus_bigradius_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_torus_bigradius_spin"));
}

static void	init_gtk_object_third_adds(t_env *e)
{
	e->ui->obj_nav_prev_btn = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_nav_prev_btn"));
	e->ui->obj_nav_next_btn = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_nav_next_btn"));
	e->ui->obj_nav_del_btn = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_nav_del_btn"));
	e->ui->obj_nav_add_type_combo = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_nav_add_type_combo"));
	e->ui->obj_nav_add_btn = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_nav_add_btn"));
	e->ui->obj_nav_jump_combo = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_nav_jump_combo"));
	if (e->gen_objects->length < 2)
	{
		gtk_widget_set_sensitive(e->ui->obj_nav_prev_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->obj_nav_next_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->obj_nav_del_btn, FALSE);
	}
}

void		init_gtk_object(t_env *e)
{
	e->ui->obj_list_box = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_box"));
	e->ui->obj_list_id_label = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_id_label"));
	e->ui->obj_list_pos_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_pos_spin_x"));
	e->ui->obj_list_pos_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_pos_spin_y"));
	e->ui->obj_list_pos_spin_z = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_pos_spin_z"));
	e->ui->obj_list_dir_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_dir_spin_x"));
	e->ui->obj_list_dir_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_dir_spin_y"));
	e->ui->obj_list_dir_spin_z = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_dir_spin_z"));
	e->ui->obj_list_diff_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_diff_spin_x"));
	e->ui->obj_list_diff_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_diff_spin_y"));
	init_gtk_object_first_adds(e);
	init_gtk_object_second_adds(e);
	init_gtk_object_third_adds(e);
}

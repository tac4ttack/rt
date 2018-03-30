/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cb_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:00:38 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:00:39 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_cb_object_first_adds(t_env *e)
{
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_spec_spin_y), \
	"value-changed", G_CALLBACK(cb_obj_spec_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_spec_spin_z), \
	"value-changed", G_CALLBACK(cb_obj_spec_z), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_reflex_spin), \
	"value-changed", G_CALLBACK(cb_obj_reflex), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_refrac_spin), \
	"value-changed", G_CALLBACK(cb_obj_refrac), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_opacity_spin), \
	"value-changed", G_CALLBACK(cb_obj_opacity), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_color_btn), \
	"color-set", G_CALLBACK(cb_obj_color), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_cone_angle_spin), \
	"value-changed", G_CALLBACK(cb_cone_angle), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_cylinder_radius_spin), \
	"value-changed", G_CALLBACK(cb_cylinder_radius), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_ellipsoid_axis_spin_x), \
	"value-changed", G_CALLBACK(cb_ellipsoid_axis_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_ellipsoid_axis_spin_y), \
	"value-changed", G_CALLBACK(cb_ellipsoid_axis_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_ellipsoid_axis_spin_z), \
	"value-changed", G_CALLBACK(cb_ellipsoid_axis_z), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_ellipsoid_radius_spin), \
	"value-changed", G_CALLBACK(cb_ellipsoid_radius), (gpointer)e);
}

static void	init_cb_object_second_adds(t_env *e)
{
	g_signal_connect(GTK_WIDGET(e->ui->obj_sphere_radius_spin), \
	"value-changed", G_CALLBACK(cb_sphere_radius), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_torus_bigradius_spin), \
	"value-changed", G_CALLBACK(cb_torus_radius_big), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_torus_lilradius_spin), \
	"value-changed", G_CALLBACK(cb_torus_radius_lil), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_nav_jump_combo), \
	"changed", G_CALLBACK(cb_obj_jump_combo), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_nav_prev_btn), \
	"clicked", G_CALLBACK(cb_obj_nav_prev), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_nav_next_btn), \
	"clicked", G_CALLBACK(cb_obj_nav_next), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_nav_del_btn), \
	"clicked", G_CALLBACK(cb_obj_nav_del), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_nav_add_type_combo), \
	"changed", G_CALLBACK(cb_obj_combo_type), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_nav_add_btn), \
	"clicked", G_CALLBACK(cb_obj_nav_add), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->tool_play_btn), \
	"clicked", G_CALLBACK(cb_play_btn), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->tool_stop_btn), \
	"clicked", G_CALLBACK(cb_stop_btn), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->tool_render_btn), \
	"clicked", G_CALLBACK(cb_render_btn), (gpointer)e);
}

static void	init_cb_object_third_adds(t_env *e)
{
	g_signal_connect(GTK_WIDGET(e->ui->tool_export_btn), \
	"clicked", G_CALLBACK(cb_export_btn), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->tool_about_btn), \
	"clicked", G_CALLBACK(cb_about_btn), (gpointer)e);
}

void		init_cb_object(t_env *e)
{
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_pos_spin_x), \
	"value-changed", G_CALLBACK(cb_obj_pos_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_pos_spin_y), \
	"value-changed", G_CALLBACK(cb_obj_pos_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_pos_spin_z), \
	"value-changed", G_CALLBACK(cb_obj_pos_z), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_dir_spin_x), \
	"value-changed", G_CALLBACK(cb_obj_dir_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_dir_spin_y), \
	"value-changed", G_CALLBACK(cb_obj_dir_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_dir_spin_z), \
	"value-changed", G_CALLBACK(cb_obj_dir_z), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_diff_spin_x), \
	"value-changed", G_CALLBACK(cb_obj_diff_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_diff_spin_y), \
	"value-changed", G_CALLBACK(cb_obj_diff_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_diff_spin_z), \
	"value-changed", G_CALLBACK(cb_obj_diff_z), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_spec_spin_x), \
	"value-changed", G_CALLBACK(cb_obj_spec_x), (gpointer)e);
	init_cb_object_first_adds(e);
	init_cb_object_second_adds(e);
	init_cb_object_third_adds(e);
}

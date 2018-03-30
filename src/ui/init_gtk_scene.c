#include "rt.h"

static void	init_gtk_scene_adds(t_env *e)
{
	e->ui->scene_supersampling_scale = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "scene_supersampling_scale"));
	gtk_scale_add_mark(GTK_SCALE(e->ui->scene_supersampling_scale), \
	1, GTK_POS_BOTTOM, "x1");
	gtk_scale_add_mark(GTK_SCALE(e->ui->scene_supersampling_scale), \
	2, GTK_POS_BOTTOM, "x2");
	gtk_scale_add_mark(GTK_SCALE(e->ui->scene_supersampling_scale), \
	3, GTK_POS_BOTTOM, "x4");
	gtk_scale_add_mark(GTK_SCALE(e->ui->scene_supersampling_scale), \
	4, GTK_POS_BOTTOM, "x8");
	gtk_scale_add_mark(GTK_SCALE(e->ui->scene_supersampling_scale), \
	5, GTK_POS_BOTTOM, "x16");
	e->ui->scene_postproc_bw_radio = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "scene_postproc_bw_radio"));
	e->ui->scene_postproc_sepia_radio = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "scene_postproc_sepia_radio"));
	e->ui->scene_postproc_none_radio = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "scene_postproc_none_radio"));
	e->ui->scene_postproc_invert_check = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "scene_postproc_invert_check"));
}

void		init_gtk_scene(t_env *e)
{
	e->ui->scene_resolution_width_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "scene_resolution_width_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)\
	e->ui->scene_resolution_width_spin, (gdouble)e->scene->win_w);
	e->ui->scene_resolution_height_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "scene_resolution_height_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)\
	e->ui->scene_resolution_height_spin, (gdouble)e->scene->win_h);
	e->ui->scene_ambient_red_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "scene_ambient_red_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->scene_ambient_red_spin, \
	(gdouble)e->scene->ambient.x);
	e->ui->scene_ambient_green_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "scene_ambient_green_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->scene_ambient_green_spin, \
	(gdouble)e->scene->ambient.y);
	e->ui->scene_ambient_blue_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "scene_ambient_blue_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->scene_ambient_blue_spin, \
	(gdouble)e->scene->ambient.z);
	e->ui->scene_depth_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "scene_depth_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->scene_depth_spin, \
	(gdouble)e->scene->depth);
	init_gtk_scene_adds(e);
}

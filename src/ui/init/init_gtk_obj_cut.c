#include "rt.h"

void	init_gtk_obj_cut(t_env *e)
{
	e->ui->obj_list_cut = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_cut"));
	e->ui->obj_cut_x_min_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_cut_x_min_spin"));
	e->ui->obj_cut_x_max_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_cut_x_max_spin"));
	e->ui->obj_cut_y_min_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_cut_y_min_spin"));
	e->ui->obj_cut_y_max_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_cut_y_max_spin"));
	e->ui->obj_cut_z_min_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_cut_z_min_spin"));
	e->ui->obj_cut_z_max_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_cut_z_max_spin"));
	e->ui->obj_cut_check = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_cut_check"));
}

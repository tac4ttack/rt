#include "rt.h"

static void		show_only_paraboloid(t_env *e)
{
	gtk_widget_hide(e->ui->obj_list_cone);
	gtk_widget_hide(e->ui->obj_list_cylinder);
	gtk_widget_hide(e->ui->obj_list_ellipsoid);
	gtk_widget_show(e->ui->obj_list_paraboloid);
	gtk_widget_hide(e->ui->obj_list_plane);
	gtk_widget_hide(e->ui->obj_list_sphere);
	gtk_widget_hide(e->ui->obj_list_torus);	
}

void	ui_obj_set_paraboloid(t_env *e, t_paraboloid *obj)
{
	show_only_paraboloid(e);
	gtk_spin_button_set_value( \
	(GtkSpinButton*)e->ui->obj_paraboloid_basedir_spin_x, \
	(gdouble)obj->base_dir.x);
	gtk_spin_button_set_value( \
	(GtkSpinButton*)e->ui->obj_paraboloid_basedir_spin_y,\
	(gdouble)obj->base_dir.y);
	gtk_spin_button_set_value( \
	(GtkSpinButton*)e->ui->obj_paraboloid_basedir_spin_z,\
	(gdouble)obj->base_dir.z);
	gtk_spin_button_set_value( \
	(GtkSpinButton*)e->ui->obj_paraboloid_height_spin,\
	(gdouble)obj->height);
	gtk_spin_button_set_value( \
	(GtkSpinButton*)e->ui->obj_paraboloid_radius_spin,\
	(gdouble)obj->radius);
}

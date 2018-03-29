#include "rt.h"

static void		show_only_sphere(t_env *e)
{	
	gtk_widget_hide(e->ui->obj_list_cone);
	gtk_widget_hide(e->ui->obj_list_cylinder);
	gtk_widget_hide(e->ui->obj_list_ellipsoid);
	gtk_widget_hide(e->ui->obj_list_paraboloid);
	gtk_widget_hide(e->ui->obj_list_plane);
	gtk_widget_show(e->ui->obj_list_sphere);
	gtk_widget_hide(e->ui->obj_list_torus);	
}

void	ui_obj_set_sphere(t_env *e, t_sphere *obj)
{
	show_only_sphere(e);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_sphere_radius_spin, \
	(gdouble)obj->radius);
}

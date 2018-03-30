#include "rt.h"

static void		show_only_plane(t_env *e)
{
	gtk_widget_hide(e->ui->obj_list_cone);
	gtk_widget_hide(e->ui->obj_list_cylinder);
	gtk_widget_hide(e->ui->obj_list_ellipsoid);
	gtk_widget_show(e->ui->obj_list_plane);
	gtk_widget_hide(e->ui->obj_list_sphere);
	gtk_widget_hide(e->ui->obj_list_torus);	
}

void	ui_obj_set_plane(t_env *e, t_plane *obj)
{
	(void)obj;
	show_only_plane(e);
}

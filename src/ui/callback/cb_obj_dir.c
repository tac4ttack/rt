#include "rt.h"

gboolean		cb_obj_dir_x(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target; 
	value = gtk_spin_button_get_value(spin);
	obj->dir.x = (float)value;
	return TRUE;
}

gboolean		cb_obj_dir_y(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	obj->dir.y = (float)value;
	return TRUE;
}

gboolean		cb_obj_dir_z(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	obj->dir.z = (float)value;
	return TRUE;
}

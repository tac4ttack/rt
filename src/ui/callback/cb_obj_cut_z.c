#include "rt.h"

gboolean		cb_obj_cut_z_min(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	obj->cut_min.z = (float)value;
	return (TRUE);
}

gboolean		cb_obj_cut_z_max(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	obj->cut_max.z = (float)value;
	return (TRUE);
}


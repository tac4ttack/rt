#include "rt.h"

gboolean		cb_obj_pos_x(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target; 
	value = gtk_spin_button_get_value(spin);
	obj->pos.x = (float)value;
	return TRUE;
}

gboolean		cb_obj_pos_y(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	obj->pos.y = (float)value;
	return TRUE;
}

gboolean		cb_obj_pos_z(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	obj->pos.z = (float)value;
	return TRUE;
}

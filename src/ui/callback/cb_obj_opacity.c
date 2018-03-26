#include "rt.h"

gboolean		cb_obj_opacity(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target; 
	value = gtk_spin_button_get_value(spin);
	obj->opacity = (float)value;
	return TRUE;
}

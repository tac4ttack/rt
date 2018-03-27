#include "rt.h"

gboolean		cb_obj_refrac(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target; 
	value = gtk_spin_button_get_value(spin);
	if (value > 0 && value < 1)
		value = 1;
	gtk_spin_button_set_value(spin, value);
	obj->refract = (float)value;
	return TRUE;
}

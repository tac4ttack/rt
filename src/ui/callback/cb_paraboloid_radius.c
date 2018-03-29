#include "rt.h"

gboolean			cb_paraboloid_radius(GtkSpinButton *spin, gpointer data)
{
	gdouble 		value;
	t_env 			*e;
	t_paraboloid	*paraboloid;

	e = data;
	paraboloid = e->gen_objects->mem + e->target; 
	value = gtk_spin_button_get_value(spin);
	paraboloid->radius = (float)value;
	return TRUE;
}

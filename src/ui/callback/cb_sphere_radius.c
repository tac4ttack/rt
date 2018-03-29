#include "rt.h"

gboolean	cb_sphere_radius(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;
	t_sphere	*sphere;

	e = data;
	sphere = e->gen_objects->mem + e->target; 
	value = gtk_spin_button_get_value(spin);
	sphere->radius = (float)value;
	return TRUE;
}

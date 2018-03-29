#include "rt.h"

gboolean		cb_cylinder_radius(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;
	t_cylinder	*cylinder;

	e = data;
	cylinder = e->gen_objects->mem + e->target; 
	value = gtk_spin_button_get_value(spin);
	cylinder->radius = (float)value;
	return TRUE;
}

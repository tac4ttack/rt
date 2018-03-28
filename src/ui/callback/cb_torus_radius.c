#include "rt.h"

gboolean		cb_torus_radius_lil(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;
	t_torus		*torus;

	e = data;
	torus = e->gen_objects->mem + e->target; 
	value = gtk_spin_button_get_value(spin);
	torus->lil_radius = (float)value;
	return TRUE;
}

gboolean		cb_torus_radius_big(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;
	t_torus		*torus;

	e = data;
	torus = e->gen_objects->mem + e->target; 
	value = gtk_spin_button_get_value(spin);
	torus->big_radius = (float)value;
	return TRUE;
}

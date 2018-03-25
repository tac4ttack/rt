#include "rt.h"

gboolean		cb_light_pos_x(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;

	e = data;
	value = gtk_spin_button_get_value(spin);
	ACTIVELIGHT.pos.x = (float)value;
	return TRUE;
}

gboolean		cb_light_pos_y(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;

	e = data;
	value = gtk_spin_button_get_value(spin);
	ACTIVELIGHT.pos.y = (float)value;
	return TRUE;
}

gboolean		cb_light_pos_z(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;

	e = data;
	value = gtk_spin_button_get_value(spin);
	ACTIVELIGHT.pos.z = (float)value;
	return TRUE;
}

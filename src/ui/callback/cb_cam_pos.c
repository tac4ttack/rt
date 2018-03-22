#include "rt.h"

gboolean		cb_cam_pos_x(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;

	e = data;
	value = gtk_spin_button_get_value(spin);
	ACTIVECAM.pos.x = (float)value;
	return TRUE;
}

gboolean		cb_cam_pos_y(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env		*e;

	e = data;
	value = gtk_spin_button_get_value(spin);
	ACTIVECAM.pos.y = (float)value;
	return TRUE;
}

gboolean		cb_cam_pos_z(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env		*e;

	e = data;
	value = gtk_spin_button_get_value(spin);
	ACTIVECAM.pos.z = (float)value;
	return TRUE;
}


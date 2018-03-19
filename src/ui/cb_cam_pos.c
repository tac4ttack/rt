#include "rt.h"

gboolean	cb_cam_pos_x(GtkSpinButton *spin, gpointer data)
{
	gint 	value;
	t_env *e;

	e = data;
	value = gtk_spin_button_get_value_as_int(spin);
	ACTIVECAM.pos.x = (int)value;
	return FALSE;
}

gboolean	cb_cam_pos_y(GtkSpinButton *spin, gpointer data)
{
	gint 	value;
	t_env	*e;

	e = data;
	value = gtk_spin_button_get_value_as_int(spin);
	ACTIVECAM.pos.y = (int)value;
	return FALSE;
}

gboolean	cb_cam_pos_z(GtkSpinButton *spin, gpointer data)
{
	gint 	value;
	t_env	*e;

	e = data;
	value = gtk_spin_button_get_value_as_int(spin);
	ACTIVECAM.pos.z = (int)value;
	return FALSE;
}


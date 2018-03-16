#include "rt.h"


gboolean	cb_ambient_red_update(GtkSpinButton *spin, gpointer data)
{
	gfloat 	value;
	t_env *e;

	e = data;
	value = gtk_spin_button_get_value(spin);
	e->scene->ambient.x = (float)value;
	return FALSE;
}

gboolean	cb_ambient_green_update(GtkSpinButton *spin, gpointer data)
{
	gfloat 	value;
	t_env *e;

	e = data;
	value = gtk_spin_button_get_value(spin);
	e->scene->ambient.y = (float)value;
	return FALSE;
}
gboolean	cb_ambient_blue_update(GtkSpinButton *spin, gpointer data)
{
	gfloat 	value;
	t_env *e;

	e = data;
	value = gtk_spin_button_get_value(spin);
	e->scene->ambient.z = (float)value;
	return FALSE;
}

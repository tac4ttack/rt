#include "rt.h"

gboolean	cb_depth_update(GtkSpinButton *spin, gpointer data)
{
	gint 	value;
	t_env *e;

	e = data;
	value = gtk_spin_button_get_value_as_int(spin);
	e->scene->depth = (int)value;
	return FALSE;
}

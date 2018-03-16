#include "rt.h"


gboolean	cb_width_update(GtkSpinButton *spin, gpointer data)
{
	gint 	value;
	t_env *e;

	e = data;
	value = gtk_spin_button_get_value_as_int(spin);
	printf("width has changed! it was %d, it is now %d\n", e->scene->win_w, (int)value);
	return FALSE;
}


gboolean	cb_height_update(GtkSpinButton *spin, gpointer data)
{
	gint 	value;
	t_env *e;

	e = data;
	value = gtk_spin_button_get_value_as_int(spin);
	printf("height has changed! it was %d, it is now %d\n", e->scene->win_h, (int)value);
	return FALSE;
}

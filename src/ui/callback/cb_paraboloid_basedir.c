#include "rt.h"

gboolean			cb_paraboloid_basedir_x(GtkSpinButton *spin, gpointer data)
{
	gdouble 		value;
	t_env	 		*e;
	t_paraboloid	*paraboloid;
	
	e = data;
	paraboloid = e->gen_objects->mem + e->target; 
	value = gtk_spin_button_get_value(spin);
	paraboloid->base_dir.x = (float)value;
	return TRUE;
}

gboolean			cb_paraboloid_basedir_y(GtkSpinButton *spin, gpointer data)
{
	gdouble 		value;
	t_env	 		*e;
	t_paraboloid	*paraboloid;
	
	e = data;
	paraboloid = e->gen_objects->mem + e->target; 
	value = gtk_spin_button_get_value(spin);
	paraboloid->base_dir.y = (float)value;
	return TRUE;
}

gboolean			cb_paraboloid_basedir_z(GtkSpinButton *spin, gpointer data)
{
	gdouble 		value;
	t_env	 		*e;
	t_paraboloid	*paraboloid;
	
	e = data;
	paraboloid = e->gen_objects->mem + e->target; 
	value = gtk_spin_button_get_value(spin);
	paraboloid->base_dir.z = (float)value;
	return TRUE;
}

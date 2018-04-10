#include "rt.h"

gboolean		cb_obj_cut_z_min(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	// if (obj->type == OBJ_CONE || obj->type == OBJ_CYLINDER || 
	// 	obj->type == OBJ_PLANE || obj->type == OBJ_SPHERE)
	if (obj->type == OBJ_SPHERE)
	{
		value = gtk_spin_button_get_value(spin);
		obj->cut_min.z = (float)value;
	}
	return (TRUE);
}

gboolean		cb_obj_cut_z_max(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	// if (obj->type == OBJ_CONE || obj->type == OBJ_CYLINDER || 
	// 	obj->type == OBJ_PLANE || obj->type == OBJ_SPHERE)
	if (obj->type == OBJ_SPHERE)
	{
		value = gtk_spin_button_get_value(spin);
		obj->cut_max.z = (float)value;
	}
	return (TRUE);
}


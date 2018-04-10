#include "rt.h"

gboolean		cb_obj_cut_x_min(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	// if (obj->type == OBJ_CONE || obj->type == OBJ_CYLINDER || 
		// obj->type == OBJ_PLANE || obj->type == OBJ_SPHERE)
	if (obj->type == OBJ_SPHERE)
	{
		value = gtk_spin_button_get_value(spin);
		obj->cut_min.x = (float)value;
	}
	return (TRUE);
}

gboolean		cb_obj_cut_x_max(GtkSpinButton *spin, gpointer data)
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
		obj->cut_max.x = (float)value;
	}
	return (TRUE);
}


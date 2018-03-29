#include "rt.h"

void			cb_obj_nav_prev(GtkButton *btn, gpointer data)
{
	t_env		*e;
	t_object	*obj;
	int			obj_index;

	(void)btn;
	e = data;
	obj = e->gen_objects->mem + e->target;
	obj_index = gen_get_ptr_index(e->gen_objects, obj);
	if (obj_index == 0)
	{
		obj = (t_object*)gen_get_index_ptr(e->gen_objects, e->gen_objects->length - 1);
		e->target = (void*)obj - e->gen_objects->mem;
	}
	 else
	{
		e->target = e->target - obj->size;
		obj = e->gen_objects->mem + e->target;
	}
	ui_obj_update(e, obj);
}

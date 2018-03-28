#include "rt.h"

void			cb_obj_nav_next(GtkButton *btn, gpointer data)
{
	t_env		*e;
	t_object	*obj;
	int			obj_index;

	(void)btn;
	e = data;
	obj = e->gen_objects->mem + e->target;
	obj_index = gen_get_ptr_index(e->gen_objects, obj);
	if (obj_index + 1 == (int)(e->gen_objects->length))
		e->target = 0;
	else
	 	e->target = e->target + obj->size;
	obj = e->gen_objects->mem + e->target;
	ui_obj_update(e, obj);
}

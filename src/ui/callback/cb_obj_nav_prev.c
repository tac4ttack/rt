#include "rt.h"

void		cb_obj_nav_prev(GtkButton *btn, gpointer data)
{
	t_env	*e;
	t_object	*obj;

	(void)btn;
	e = data;
	obj = e->gen_objects->mem + e->target;
	if (obj->id - NCAM == 1)
	{
		while (obj->id - (int)NCAM< (int)e->gen_objects->length)
		{
			e->target += obj->size;
			obj = e->gen_objects->mem + e->target;
		}
	}
	else
		e->target = e->target - obj->size;
	obj = e->gen_objects->mem + e->target;
	ui_obj_update(e, obj);
	ui_obj_set_id(e, obj);
}

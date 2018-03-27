#include "rt.h"

void		cb_obj_nav_next(GtkButton *btn, gpointer data)
{
	t_env	*e;
	t_object	*obj;

	(void)btn;
	e = data;
	obj = e->gen_objects->mem + e->target;
	if (obj->id + 1 > (int)(e->gen_objects->length + NCAM))
		e->target = 0;
	else
		e->target = e->target + obj->size;
	obj = e->gen_objects->mem + e->target;
	ui_obj_update(e, obj);
	ui_obj_set_id(e, obj);
}

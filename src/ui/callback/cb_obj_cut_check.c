#include "rt.h"

void	cb_obj_cut_check(GtkToggleButton *btn, gpointer data)
{
	t_env		*e;
	t_object	*obj;

	(void)btn;
	e = data;
	obj = e->gen_objects->mem + e->target;
	if (obj->flags & OBJ_FLAG_CUT)
		obj->flags ^= OBJ_FLAG_CUT;
	else
		obj->flags |= OBJ_FLAG_CUT;
}

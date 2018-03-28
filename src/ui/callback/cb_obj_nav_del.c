#include "rt.h"

void			cb_obj_nav_del(GtkButton *btn, gpointer data)
{
	t_env		*e;
	t_object	*obj;

	(void)btn;
	e = data;
	obj = e->gen_objects->mem + e->target;
	if (e->gen_objects->length == 1)
		ft_putendl("why did u du dis? :(((((");
	else
	{
		e->gen_objects->remove_mem_index(e->gen_objects, e->target);
		if (e->gen_objects->length == 1)
		{
			gtk_widget_set_sensitive(e->ui->obj_nav_prev_btn, FALSE);
			gtk_widget_set_sensitive(e->ui->obj_nav_next_btn, FALSE);
			gtk_widget_set_sensitive(e->ui->obj_nav_del_btn, FALSE);
		}
		if (!(cl_replace_buffer(e->cl, e->gen_objects->mem_size, 1)))
			s_error("\x1b[2;31mFailed replacing objects buffer\x1b[0m", e);
		e->target = -1;
		ui_obj_update(e, obj);
		// fonction maj combolist
	}
}

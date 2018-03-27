#include "rt.h"


// static void			cb_obj_nav_add_jump_to_last(t_env *e)
// {
// 	t_object	*obj;

// 	obj = e->gen_objects->mem + e->target;
// // 	while (obj->id - (int)NCAM< (int)e->gen_objects->length)
// // 	{
// // 		e->target += obj->size;
// // 		obj = e->gen_objects->mem + e->target;
// // 	}
// // 	obj = e->gen_objects->mem + e->target;
// // 	ui_obj_update(e, obj);
// // 	ui_obj_set_id(e, obj);
// }

void			cb_obj_nav_add(GtkButton *btn, gpointer data)
{
	t_env		*e;
	gint		index;
	

	(void)btn;
	e = data;
	
	t_object *obj;
	obj = e->gen_objects->mem + e->target;
	
	index = gen_get_ptr_index(e->gen_objects, obj);
	printf("test %d\n", index);

	// index = gtk_combo_box_get_active((GtkComboBox*)e->ui->obj_nav_add_type_combo);
	// // if (index == 0)
	// // 	ui_add_cone(e);
	// // else if (index == 1)
	// // 	ui_add_cylinder(e);
	// // else if (index == 2)
	// // 	ui_add_ellipsoid(e);
	// // else if (index == 3)
	// // 	ui_add_paraboloid(e);
	// // else if (index == 4)
	// // 	ui_add_plane(e);
	// // else if (index == 5)
	// // 	ui_add_sphere(e);
	// // else if (index == 6)
	// // 	ui_add_torus(e);
	// cb_obj_nav_add_jump_to_last(e);
	// gtk_combo_box_set_active((GtkComboBox*)e->ui->obj_nav_add_type_combo, -1);
	// gtk_widget_set_sensitive(e->ui->obj_nav_add_btn, FALSE);
}

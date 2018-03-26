#include "rt.h"

void			cb_obj_color(GtkColorButton *button, gpointer data)
{
	t_env 		*e;
	GdkRGBA		new_color;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	new_color.alpha = 1;
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(button), &new_color);
	obj->color = ui_gdkrgba_to_int(new_color);
	e->ui->obj_color = new_color;
	
}

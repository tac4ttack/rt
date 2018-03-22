#include "rt.h"


void	cb_render_update_size(GtkContainer *box, gpointer data)
{
	t_env *e;
	cl_int2 zone;

	e = data;
	(void)box;
	zone.x = gtk_widget_get_allocated_width(e->ui->render);
	zone.y = gtk_widget_get_allocated_height(e->ui->render);
	gtk_widget_queue_draw_area(e->ui->render, 0, 0, zone.x, zone.y);
}

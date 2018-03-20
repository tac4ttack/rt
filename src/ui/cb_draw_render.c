#include "rt.h"


gboolean cb_draw_render(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	t_env *e;
	(void)widget;
	e = data;
	update_fps(&e->fps);
	if (e->ui->redraw == 1)
		opencl_draw(e);

//	gtk_widget_grab_focus(widget); /// fou le focus sur le render

//	1ere methode
	gdk_cairo_set_source_pixbuf(cr, e->ui->pixbuf, 1, 1);
//	2nde methode
//	if (e->ui->surface)
//		cairo_surface_destroy(e->ui->surface);
//	e->ui->surface = gdk_cairo_surface_create_from_pixbuf (e->ui->pixbuf, 1, NULL);
//	cairo_set_source_surface(cr, e->ui->surface, 0, 0);

	cairo_paint(cr);
	return FALSE;
}
